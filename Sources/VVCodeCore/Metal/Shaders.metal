#include <metal_stdlib>
using namespace metal;

// MARK: - Shared Structures

struct TextUniforms {
    float4x4 projectionMatrix;
    float2 scrollOffset;
    float2 viewportSize;
    float2 atlasSize;
    float pxRange;
    float time;
    float2 padding;
};

// MARK: - Glyph Rendering

struct GlyphVertexIn {
    float2 position [[attribute(0)]];
    float2 texCoord [[attribute(1)]];
    float4 color [[attribute(2)]];
};

struct GlyphVertexOut {
    float4 position [[position]];
    float2 texCoord;
    float4 color;
};

// Instanced glyph rendering
struct GlyphInstance {
    float2 position;      // Screen position (top-left)
    float2 size;          // Quad size
    float2 uvOrigin;      // UV top-left in atlas
    float2 uvSize;        // UV extent
    float4 color;         // RGBA color
    uint atlasIndex;      // Atlas page (unused for now)
    uint3 padding;
};

vertex GlyphVertexOut glyphVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant GlyphInstance* instances [[buffer(0)]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    // Quad vertices (two triangles)
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),  // First triangle
        float2(1, 0), float2(1, 1), float2(0, 1)   // Second triangle
    };

    const float2 quadTexCoords[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    GlyphInstance instance = instances[instanceID];
    float2 quadPos = quadPositions[vertexID];
    float2 quadTex = quadTexCoords[vertexID];

    // Calculate world position
    float2 worldPos = instance.position + quadPos * instance.size;

    // Apply scroll offset
    float2 scrolledPos = worldPos - uniforms.scrollOffset;

    // Transform to clip space
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    // Calculate texture coordinates
    float2 texCoord = instance.uvOrigin + quadTex * instance.uvSize;

    GlyphVertexOut out;
    out.position = clipPos;
    out.texCoord = texCoord;
    out.color = instance.color;

    return out;
}

// MSDF helper: compute median of three values
float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

// Simple alpha mask fragment shader using pixel coordinates for crisp text
fragment float4 msdfFragmentShader(
    GlyphVertexOut in [[stage_in]],
    texture2d<float> atlas [[texture(0)]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    // Pixel coordinate sampling with nearest neighbor for crisp text
    constexpr sampler textureSampler(
        coord::pixel,
        address::clamp_to_edge,
        filter::nearest
    );

    // Sample alpha from grayscale texture (r8Unorm format)
    float alpha = atlas.sample(textureSampler, in.texCoord).r;

    // Apply color with sampled alpha
    return float4(in.color.rgb, in.color.a * alpha);
}

// MARK: - Selection/Background Rendering

struct QuadVertexOut {
    float4 position [[position]];
    float4 color;
};

struct SelectionQuad {
    float2 position;
    float2 size;
    float4 color;
};

vertex QuadVertexOut selectionVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant SelectionQuad* quads [[buffer(0)]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    SelectionQuad quad = quads[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 worldPos = quad.position + quadPos * quad.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    QuadVertexOut out;
    out.position = clipPos;
    out.color = quad.color;

    return out;
}

fragment float4 selectionFragmentShader(QuadVertexOut in [[stage_in]]) {
    return in.color;
}

// MARK: - Cursor Rendering (with blink)

fragment float4 cursorFragmentShader(
    QuadVertexOut in [[stage_in]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    return in.color;
}

// MARK: - Line Number Gutter

// Same as glyph rendering but with different scroll behavior (no horizontal scroll)
vertex GlyphVertexOut gutterVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant GlyphInstance* instances [[buffer(0)]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    const float2 quadTexCoords[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    GlyphInstance instance = instances[instanceID];
    float2 quadPos = quadPositions[vertexID];
    float2 quadTex = quadTexCoords[vertexID];

    // Calculate world position (no horizontal scroll for gutter)
    float2 worldPos = instance.position + quadPos * instance.size;

    // Only apply vertical scroll offset
    float2 scrolledPos = float2(worldPos.x, worldPos.y - uniforms.scrollOffset.y);

    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);
    float2 texCoord = instance.uvOrigin + quadTex * instance.uvSize;

    GlyphVertexOut out;
    out.position = clipPos;
    out.texCoord = texCoord;
    out.color = instance.color;

    return out;
}

// MARK: - Underline/Diagnostic Rendering

struct UnderlineVertex {
    float2 position;
    float4 color;
    float phase;  // For wavy underlines
};

struct UnderlineVertexOut {
    float4 position [[position]];
    float4 color;
    float phase;
    float2 localPos;
};

vertex UnderlineVertexOut underlineVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant SelectionQuad* quads [[buffer(0)]],
    constant TextUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    SelectionQuad quad = quads[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 worldPos = quad.position + quadPos * quad.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    UnderlineVertexOut out;
    out.position = clipPos;
    out.color = quad.color;
    out.phase = worldPos.x * 0.5;  // Phase based on x position
    out.localPos = quadPos * quad.size;

    return out;
}

fragment float4 wavyUnderlineFragmentShader(UnderlineVertexOut in [[stage_in]]) {
    // Create wavy pattern
    float wave = sin(in.phase + in.localPos.x * 3.14159 * 2.0) * 0.5 + 0.5;
    float height = in.localPos.y / 3.0;  // Assuming 3px height

    // Check if current pixel is on the wave
    float targetY = wave * 2.0;  // Wave amplitude
    float dist = abs(height * 3.0 - targetY);
    float alpha = 1.0 - smoothstep(0.0, 1.0, dist);

    return float4(in.color.rgb, in.color.a * alpha);
}

fragment float4 straightUnderlineFragmentShader(UnderlineVertexOut in [[stage_in]]) {
    return in.color;
}
