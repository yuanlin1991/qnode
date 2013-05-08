/*
 * See Copyright Notice in qnode.h
 */

#include "qalloc.h"
#include "qstring.h"
#include "qvalue.h"

void qvalue_destroy(qvalue_t *value) {
  if (value->type == QSTRING_TYPE) {
    qstring_destroy(value->data.str);
  }
}

int qvalue_clone(qvalue_t *value1, qvalue_t *value2) {
  if (qvalue_isstring(value2)) {
    if (qvalue_isnumber(value1)) {
      value1->data.str = qstring_new(value2->data.str);
    } else {
      value1->data.str = qstring_assign(value2->data.str);
    }

    return;
  }

  if (qvalue_isstring(value1)) {
    qstring_destroy(value1->data.str);
  }
  value1->type = QVAL_NUMBER;
  value1->data.num = value2->data.num;
}