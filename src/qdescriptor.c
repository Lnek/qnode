/*
 * See Copyright Notice in qnode.h
 */
#include "qactor.h"
#include "qassert.h"
#include "qdescriptor.h"
#include "qmalloc.h"
#include "qserver.h"

qdescriptor_t* qdescriptor_new(int fd, unsigned short type, qactor_t *actor) {
  qassert(actor);
  qassert(fd < QID_MAX);
  qdescriptor_t *desc = g_server->descriptors[fd];
  if (desc) {
    qassert(desc);
    qassert(desc->aid == -1);
    qassert(desc->fd == fd);
  } else {
    desc = qalloc_type(qdescriptor_t);
    desc->aid = -1;
    desc->fd = fd;
    g_server->descriptors[fd] = desc;
    qlist_entry_init(&desc->entry);
  }
  desc->aid  = actor->aid;
  desc->type = type;
  qlist_add_tail(&desc->entry, &actor->desc_list);
  return desc;
}