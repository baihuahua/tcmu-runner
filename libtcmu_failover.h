/*
 * Copyright (c) 2017 Red Hat, Inc.
 *
 * This file is licensed to you under your choice of the GNU Lesser
 * General Public License, version 2.1 or any later version (LGPLv2.1 or
 * later), or the Apache License 2.0.
 */

#ifndef __LIBTCMU_FAILOVER_H
#define __LIBTCMU_FAILOVER_H

#include "pthread.h"

#include "ccan/list/list.h"

#include "libtcmu_aio.h"

#define TCMUR_DEV_FLAG_FORMATTING	(1 << 0)
#define TCMUR_DEV_FLAG_IN_RECOVERY	(1 << 1)
#define TCMUR_DEV_FLAG_IS_OPEN		(1 << 2)
#define TCMUR_DEV_FLAG_STOPPING		(1 << 3)
#define TCMUR_DEV_FLAG_STOPPED		(1 << 4)

#define TCMUR_UA_DEV_SIZE_CHANGED	0

enum {
	TMCUR_DEV_FAILOVER_ALL_ACTIVE,
	TMCUR_DEV_FAILOVER_IMPLICIT,
	TMCUR_DEV_FAILOVER_EXPLICIT,
};

enum {
	TCMUR_DEV_LOCK_UNLOCKED,
	TCMUR_DEV_LOCK_LOCKED,
	TCMUR_DEV_LOCK_LOCKING,
};

bool tcmu_dev_in_recovery(struct tcmu_device *dev);
void tcmu_cancel_recovery(struct tcmu_device *dev);
int tcmu_cancel_lock_thread(struct tcmu_device *dev);

void tcmu_notify_conn_lost(struct tcmu_device *dev);
void tcmu_notify_lock_lost(struct tcmu_device *dev);

int __tcmu_reopen_dev(struct tcmu_device *dev, bool in_lock_thread, int retries);
int tcmu_reopen_dev(struct tcmu_device *dev, bool in_lock_thread, int retries);

int tcmu_acquire_dev_lock(struct tcmu_device *dev, bool is_sync, uint16_t tag);
void tcmu_release_dev_lock(struct tcmu_device *dev);
int tcmu_get_lock_tag(struct tcmu_device *dev, uint16_t *tag);

#endif
