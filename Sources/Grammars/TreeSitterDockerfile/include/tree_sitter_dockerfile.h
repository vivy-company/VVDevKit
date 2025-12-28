#ifndef TREE_SITTER_DOCKERFILE_H_
#define TREE_SITTER_DOCKERFILE_H_

typedef struct TSLanguage TSLanguage;

#ifdef __cplusplus
extern "C" {
#endif

const TSLanguage *tree_sitter_dockerfile(void);

#ifdef __cplusplus
}
#endif

#endif
