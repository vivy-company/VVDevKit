//  MarkdownShaders.metal
//  VVMarkdown
//
//  Metal shaders for markdown rendering

#include <metal_stdlib>
using namespace metal;

// MARK: - Shared Structures

struct MarkdownUniforms {
    float4x4 projectionMatrix;
    float2 scrollOffset;
    float2 viewportSize;
    float2 atlasSize;
    float time;
    float padding;
};

// MARK: - Glyph Rendering (reuses core text rendering approach)

struct GlyphVertexOut {
    float4 position [[position]];
    float2 texCoord;
    float4 color;
};

struct GlyphInstance {
    float2 position;
    float2 size;
    float2 uvOrigin;
    float2 uvSize;
    float4 color;
    uint atlasIndex;
    uint3 padding;
};

vertex GlyphVertexOut markdownGlyphVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant GlyphInstance* instances [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
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

    float2 worldPos = instance.position + quadPos * instance.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    float2 texCoord = instance.uvOrigin + quadTex * instance.uvSize;

    GlyphVertexOut out;
    out.position = clipPos;
    out.texCoord = texCoord;
    out.color = instance.color;
    return out;
}

fragment float4 markdownGlyphFragmentShader(
    GlyphVertexOut in [[stage_in]],
    texture2d<float> atlas [[texture(0)]]
) {
    constexpr sampler textureSampler(
        coord::pixel,
        address::clamp_to_edge,
        filter::nearest
    );

    float alpha = atlas.sample(textureSampler, in.texCoord).r;
    return float4(in.color.rgb, in.color.a * alpha);
}

fragment float4 markdownColorGlyphFragmentShader(
    GlyphVertexOut in [[stage_in]],
    texture2d<float> atlas [[texture(0)]]
) {
    constexpr sampler textureSampler(
        coord::pixel,
        address::clamp_to_edge,
        filter::nearest
    );

    float4 rgba = atlas.sample(textureSampler, in.texCoord);
    return float4(rgba.rgb * in.color.rgb, rgba.a * in.color.a);
}

// MARK: - Quad Rendering (backgrounds, borders)

struct QuadVertexOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
    float2 size;
};

struct QuadInstance {
    float2 position;
    float2 size;
    float4 color;
    float cornerRadius;
    float borderWidth;
    float2 padding;
};

vertex QuadVertexOut markdownQuadVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant QuadInstance* quads [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    QuadInstance quad = quads[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 worldPos = quad.position + quadPos * quad.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    QuadVertexOut out;
    out.position = clipPos;
    out.color = quad.color;
    out.localPos = quadPos * quad.size;
    out.size = quad.size;
    return out;
}

fragment float4 markdownQuadFragmentShader(QuadVertexOut in [[stage_in]]) {
    return in.color;
}

// Rounded rectangle fragment shader
fragment float4 markdownRoundedQuadFragmentShader(
    QuadVertexOut in [[stage_in]],
    constant QuadInstance* quads [[buffer(0)]]
) {
    float2 halfSize = in.size * 0.5;
    float2 center = halfSize;
    float2 pos = in.localPos;

    // Distance from center
    float2 d = abs(pos - center) - halfSize + quads[0].cornerRadius;
    float dist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - quads[0].cornerRadius;

    // Anti-aliased edge
    float alpha = 1.0 - smoothstep(-1.0, 1.0, dist);

    return float4(in.color.rgb, in.color.a * alpha);
}

// MARK: - Pie Slice Rendering

struct PieSliceInstance {
    float2 center;
    float radius;
    float startAngle;
    float endAngle;
    float padding0;
    float padding1;
    float padding2;
    float4 color;
};

struct PieSliceVertexOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
    float radius;
    float startAngle;
    float endAngle;
};

vertex PieSliceVertexOut pieSliceVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant PieSliceInstance* slices [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    PieSliceInstance slice = slices[instanceID];
    float2 quadPos = quadPositions[vertexID];
    float2 local = (quadPos - 0.5) * 2.0 * slice.radius;
    float2 worldPos = slice.center + local;

    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    PieSliceVertexOut out;
    out.position = clipPos;
    out.color = slice.color;
    out.localPos = local;
    out.radius = slice.radius;
    out.startAngle = slice.startAngle;
    out.endAngle = slice.endAngle;
    return out;
}

fragment float4 pieSliceFragmentShader(PieSliceVertexOut in [[stage_in]]) {
    float dist = length(in.localPos);
    if (dist > in.radius) {
        discard_fragment();
    }

    float angle = atan2(in.localPos.y, in.localPos.x);
    if (angle < 0.0) {
        angle += 6.2831853;
    }
    float start = in.startAngle;
    float end = in.endAngle;
    if (end < start) {
        end += 6.2831853;
    }
    float cmpAngle = angle;
    if (cmpAngle < start) {
        cmpAngle += 6.2831853;
    }
    if (cmpAngle < start || cmpAngle > end) {
        discard_fragment();
    }

    float edge = smoothstep(in.radius - 1.0, in.radius, dist);
    return float4(in.color.rgb, in.color.a * (1.0 - edge));
}

// MARK: - Block Quote Border

struct BlockQuoteBorderOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
};

struct BlockQuoteBorder {
    float2 position;
    float2 size;
    float4 color;
    float borderWidth;
    float3 padding;
};

vertex BlockQuoteBorderOut blockQuoteBorderVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant BlockQuoteBorder* borders [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    BlockQuoteBorder border = borders[instanceID];
    float2 quadPos = quadPositions[vertexID];

    // Only render the left border strip
    float2 borderSize = float2(border.borderWidth, border.size.y);
    float2 worldPos = border.position + quadPos * borderSize;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    BlockQuoteBorderOut out;
    out.position = clipPos;
    out.color = border.color;
    out.localPos = quadPos;
    return out;
}

fragment float4 blockQuoteBorderFragmentShader(BlockQuoteBorderOut in [[stage_in]]) {
    // Slight rounded edges at top and bottom
    float edgeDist = min(in.localPos.y, 1.0 - in.localPos.y);
    float alpha = smoothstep(0.0, 0.1, edgeDist);
    return float4(in.color.rgb, in.color.a * alpha);
}

// MARK: - Thematic Break (Horizontal Rule)

struct ThematicBreakOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
    float width;
};

struct ThematicBreak {
    float2 position;
    float width;
    float height;
    float4 color;
};

vertex ThematicBreakOut thematicBreakVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant ThematicBreak* breaks [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    ThematicBreak br = breaks[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 size = float2(br.width, br.height);
    float2 worldPos = br.position + quadPos * size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    ThematicBreakOut out;
    out.position = clipPos;
    out.color = br.color;
    out.localPos = quadPos;
    out.width = br.width;
    return out;
}

fragment float4 thematicBreakFragmentShader(ThematicBreakOut in [[stage_in]]) {
    // Gradient fade at edges
    float edgeFade = smoothstep(0.0, 0.1, in.localPos.x) * smoothstep(1.0, 0.9, in.localPos.x);
    return float4(in.color.rgb, in.color.a * edgeFade);
}

// MARK: - List Bullet

struct BulletOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
    uint bulletType; // 0=disc, 1=circle, 2=square
};

struct BulletInstance {
    float2 position;
    float2 size;
    float4 color;
    uint bulletType;
    uint3 padding;
};

vertex BulletOut bulletVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant BulletInstance* bullets [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    BulletInstance bullet = bullets[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 worldPos = bullet.position + quadPos * bullet.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    BulletOut out;
    out.position = clipPos;
    out.color = bullet.color;
    out.localPos = quadPos;
    out.bulletType = bullet.bulletType;
    return out;
}

fragment float4 bulletFragmentShader(BulletOut in [[stage_in]]) {
    float2 center = float2(0.5, 0.5);
    float2 pos = in.localPos;
    float dist = length(pos - center);

    float alpha = 0.0;

    if (in.bulletType == 0) {
        // Filled disc
        alpha = 1.0 - smoothstep(0.3, 0.35, dist);
    } else if (in.bulletType == 1) {
        // Circle (outline)
        float ring = abs(dist - 0.3);
        alpha = 1.0 - smoothstep(0.05, 0.08, ring);
    } else {
        // Square
        float2 d = abs(pos - center);
        float sqDist = max(d.x, d.y);
        alpha = 1.0 - smoothstep(0.25, 0.28, sqDist);
    }

    return float4(in.color.rgb, in.color.a * alpha);
}

// MARK: - Checkbox

struct CheckboxOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
    uint isChecked;
};

struct CheckboxInstance {
    float2 position;
    float2 size;
    float4 color;
    uint isChecked;
    uint3 padding;
};

vertex CheckboxOut checkboxVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant CheckboxInstance* checkboxes [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    CheckboxInstance cb = checkboxes[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 worldPos = cb.position + quadPos * cb.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    CheckboxOut out;
    out.position = clipPos;
    out.color = cb.color;
    out.localPos = quadPos;
    out.isChecked = cb.isChecked;
    return out;
}

fragment float4 checkboxFragmentShader(CheckboxOut in [[stage_in]]) {
    float2 pos = in.localPos;
    float2 center = float2(0.5, 0.5);

    // Rounded rectangle border
    float2 d = abs(pos - center) - float2(0.35, 0.35);
    float boxDist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);

    float borderAlpha = 1.0 - smoothstep(-0.05, 0.02, boxDist);

    if (in.isChecked == 1) {
        // Draw checkmark
        // Line from bottom-left to center
        float2 p1 = float2(0.2, 0.5);
        float2 p2 = float2(0.45, 0.75);
        float2 p3 = float2(0.8, 0.25);

        // Distance to first line segment
        float2 pa = pos - p1;
        float2 ba = p2 - p1;
        float h1 = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
        float d1 = length(pa - ba * h1);

        // Distance to second line segment
        float2 pb = pos - p2;
        float2 bb = p3 - p2;
        float h2 = clamp(dot(pb, bb) / dot(bb, bb), 0.0, 1.0);
        float d2 = length(pb - bb * h2);

        float checkDist = min(d1, d2);
        float checkAlpha = 1.0 - smoothstep(0.06, 0.1, checkDist);

        return float4(in.color.rgb, in.color.a * max(borderAlpha, checkAlpha));
    }

    return float4(in.color.rgb, in.color.a * borderAlpha);
}

// MARK: - Table Grid Lines

struct TableGridOut {
    float4 position [[position]];
    float4 color;
};

struct TableGridLine {
    float2 start;
    float2 end;
    float4 color;
    float lineWidth;
    float3 padding;
};

vertex TableGridOut tableGridVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant TableGridLine* lines [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    TableGridLine line = lines[instanceID];

    float2 dir = normalize(line.end - line.start);
    float2 normal = float2(-dir.y, dir.x);

    float2 positions[6];
    positions[0] = line.start - normal * line.lineWidth * 0.5;
    positions[1] = line.start + normal * line.lineWidth * 0.5;
    positions[2] = line.end - normal * line.lineWidth * 0.5;
    positions[3] = line.start + normal * line.lineWidth * 0.5;
    positions[4] = line.end + normal * line.lineWidth * 0.5;
    positions[5] = line.end - normal * line.lineWidth * 0.5;

    float2 worldPos = positions[vertexID];
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    TableGridOut out;
    out.position = clipPos;
    out.color = line.color;
    return out;
}

fragment float4 tableGridFragmentShader(TableGridOut in [[stage_in]]) {
    return in.color;
}

// MARK: - Link Underline

struct LinkUnderlineOut {
    float4 position [[position]];
    float4 color;
    float2 localPos;
};

struct LinkUnderline {
    float2 position;
    float width;
    float height;
    float4 color;
};

vertex LinkUnderlineOut linkUnderlineVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant LinkUnderline* underlines [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    LinkUnderline ul = underlines[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 size = float2(ul.width, ul.height);
    float2 worldPos = ul.position + quadPos * size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    LinkUnderlineOut out;
    out.position = clipPos;
    out.color = ul.color;
    out.localPos = quadPos;
    return out;
}

fragment float4 linkUnderlineFragmentShader(LinkUnderlineOut in [[stage_in]]) {
    // Simple solid underline
    return in.color;
}

// MARK: - Strikethrough Line

struct StrikethroughOut {
    float4 position [[position]];
    float4 color;
};

struct Strikethrough {
    float2 position;
    float width;
    float height;
    float4 color;
};

vertex StrikethroughOut strikethroughVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant Strikethrough* lines [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    Strikethrough line = lines[instanceID];
    float2 quadPos = quadPositions[vertexID];

    float2 size = float2(line.width, line.height);
    float2 worldPos = line.position + quadPos * size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    StrikethroughOut out;
    out.position = clipPos;
    out.color = line.color;
    return out;
}

fragment float4 strikethroughFragmentShader(StrikethroughOut in [[stage_in]]) {
    return in.color;
}

// MARK: - Image Rendering

struct ImageVertexOut {
    float4 position [[position]];
    float2 texCoord;
    float cornerRadius;
    float2 size;
    float2 localPos;
};

struct ImageInstance {
    float2 position;
    float2 size;
    float2 uvOrigin;
    float2 uvSize;
    float cornerRadius;
    float3 padding;
};

vertex ImageVertexOut imageVertexShader(
    uint vertexID [[vertex_id]],
    uint instanceID [[instance_id]],
    constant ImageInstance* images [[buffer(0)]],
    constant MarkdownUniforms& uniforms [[buffer(1)]]
) {
    const float2 quadPositions[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };
    const float2 quadTexCoords[6] = {
        float2(0, 0), float2(1, 0), float2(0, 1),
        float2(1, 0), float2(1, 1), float2(0, 1)
    };

    ImageInstance image = images[instanceID];
    float2 quadPos = quadPositions[vertexID];
    float2 quadTex = quadTexCoords[vertexID];

    float2 worldPos = image.position + quadPos * image.size;
    float2 scrolledPos = worldPos - uniforms.scrollOffset;
    float4 clipPos = uniforms.projectionMatrix * float4(scrolledPos, 0.0, 1.0);

    float2 texCoord = image.uvOrigin + quadTex * image.uvSize;

    ImageVertexOut out;
    out.position = clipPos;
    out.texCoord = texCoord;
    out.cornerRadius = image.cornerRadius;
    out.size = image.size;
    out.localPos = quadPos * image.size;
    return out;
}

fragment float4 imageFragmentShader(
    ImageVertexOut in [[stage_in]],
    texture2d<float> imageTexture [[texture(0)]],
    sampler imageSampler [[sampler(0)]]
) {
    float4 color = imageTexture.sample(imageSampler, in.texCoord);

    // Apply rounded corners if needed
    if (in.cornerRadius > 0) {
        float2 halfSize = in.size * 0.5;
        float2 center = halfSize;
        float2 pos = in.localPos;

        float2 d = abs(pos - center) - halfSize + in.cornerRadius;
        float dist = length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - in.cornerRadius;

        float alpha = 1.0 - smoothstep(-1.0, 1.0, dist);
        color.a *= alpha;
    }

    return color;
}
