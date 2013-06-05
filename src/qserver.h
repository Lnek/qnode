/*
 * See Copyright Notice in qnode.h
 */

#ifndef __QSERVER_H__
#define __QSERVER_H__

#include "qconfig.h"
#include "qcore.h"
#include "qidmap.h"
#include "qmailbox.h"
#include "qmutex.h"
#include "qtype.h"

#define QMAIN_THREAD_TID 0

struct qserver_t {
  qmailbox_t        box;
  qactor_t        **actors;       /* actor array */
  qconfig_t        *config;       /* server config */
  qdescriptor_t   **descriptors;  /* descriptor array */
  qengine_t        *engine;       /* event dispatch engine */
  qthread_t       **threads;      /* worker threads array */
  qthread_log_t   **thread_log;   /* thread log array(include main) */
  unsigned int      num_actor;    /* actor number */
  qidmap_t          id_map;       /* id map for allocate actor id */
  qmutex_t          id_map_mutex; /* mutex for id map */
};

int qserver_run(qconfig_t *config);

void qserver_new_actor(qactor_t *actor);

void qserver_worker_started();

qtid_t qserver_worker_thread();

qactor_t* qserver_get_actor(qid_t id);

/* the GLOBAL server in the system */
extern qserver_t *g_server;

extern volatile int g_quit;

#endif  /* __QSERVER_H__ */
