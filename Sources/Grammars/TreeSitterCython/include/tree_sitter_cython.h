#ifndef TREE_SITTER_CYTHON_H_
#define TREE_SITTER_CYTHON_H_

typedef struct TSLanguage TSLanguage;

#ifdef __cplusplus
extern "C" {
#endif

const TSLanguage *tree_sitter_cython(void);

#ifdef __cplusplus
}
#endif

#endif
