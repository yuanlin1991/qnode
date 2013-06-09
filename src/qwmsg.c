/*
 * See Copyright Notice in qnode.h
 */

#include "qwmsg.h"

qmsg_t*
qwmsg_start_new(qid_t aid, qid_t sender, qid_t recver) {
  qmsg_t        *msg;
  qwmsg_start_t *start;

  msg = qmsg_new(sender, recver, sizeof(qwmsg_start_t), W_START);
  if (msg == NULL) {
    return NULL;
  }

  start       = (qwmsg_start_t*)msg;
  start->aid  = aid;

  return msg;
}

qmsg_t*
qwmsg_spawn_new(qactor_t *actor, qactor_t *parent,
                lua_State *state, qid_t sender, qid_t recver) {
  qmsg_t        *msg;
  qwmsg_spawn_t *spawn;

  msg = qmsg_new(sender, recver, sizeof(qwmsg_spawn_t), W_SPAWN);
  if (msg == NULL) {
    return NULL;
  }

  spawn         = (qwmsg_spawn_t*)msg;
  spawn->aid    = actor->aid;
  spawn->parent = parent->aid;
  spawn->state  = state;
  spawn->actor  = actor;

  qactor_attach(actor, state);
  actor->parent = parent->aid;

  return msg;
}
