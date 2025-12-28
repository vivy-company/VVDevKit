#ifndef TREE_SITTER_NASM_H_
#define TREE_SITTER_NASM_H_

typedef struct TSLanguage TSLanguage;

#ifdef __cplusplus
extern "C" {
#endif

const TSLanguage *tree_sitter_nasm(void);

#ifdef __cplusplus
}
#endif

#endif
