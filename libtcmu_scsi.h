/*
 * Copyright (c) 2017 Red Hat, Inc.
 *
 * This file is licensed to you under your choice of the GNU Lesser
 * General Public License, version 2.1 or any later version (LGPLv2.1 or
 * later), or the Apache License 2.0.
 */

#ifndef __LIBTCMU_SCSI_H
#define __LIBTCMU_SCSI_H

#include <stdbool.h>
#include <inttypes.h>
#include <sys/types.h>

#include "libtcmu.h"
#include "libtcmu_common.h"

struct tcmu_device;
struct tcmulib_cmd;

/* Basic implementations of mandatory SCSI commands */
int tcmu_set_sense_data(uint8_t *sense_buf, uint8_t key, uint16_t asc_ascq);
void tcmu_set_sense_info(uint8_t *sense_buf, uint32_t info);
void tcmu_set_sense_key_specific_info(uint8_t *sense_buf, uint16_t info);
int tcmu_emulate_inquiry(struct tcmu_device *dev, struct tgt_port *port, uint8_t *cdb, struct iovec *iovec, size_t iov_cnt);
int tcmu_emulate_start_stop(struct tcmu_device *dev, uint8_t *cdb);
int tcmu_emulate_test_unit_ready(uint8_t *cdb, struct iovec *iovec, size_t iov_cnt);
int tcmu_emulate_read_capacity_10(uint64_t num_lbas, uint32_t block_size, uint8_t *cdb,
				  struct iovec *iovec, size_t iov_cnt);
int tcmu_emulate_read_capacity_16(uint64_t num_lbas, uint32_t block_size, uint8_t *cdb,
				  struct iovec *iovec, size_t iov_cnt);
int tcmu_emulate_mode_sense(struct tcmu_device *dev, uint8_t *cdb,
			    struct iovec *iovec, size_t iov_cnt);
int tcmu_emulate_mode_select(struct tcmu_device *dev, uint8_t *cdb,
			     struct iovec *iovec, size_t iov_cnt);

/* SCSI command Helpers */
typedef int (*tcmu_writesame_fn_t)(struct tcmu_device *dev, struct tcmulib_cmd *cmd,
			   uint64_t off, uint64_t len, struct iovec *iov, size_t iov_cnt);

int tcmu_handle_writesame_helper(struct tcmu_device *dev, struct tcmulib_cmd *cmd,
				      tcmu_writesame_fn_t write_same_fn);

typedef int (*tcmu_caw_fn_t)(struct tcmu_device *dev, struct tcmulib_cmd *cmd,
                              uint64_t off, uint64_t len, struct iovec *iov,
                              size_t iov_cnt);
int tcmu_handle_caw_helper(struct tcmu_device *dev, struct tcmulib_cmd *cmd,
			   tcmu_caw_fn_t caw_fn);

void tcmu_command_complete(struct tcmu_device *dev, struct tcmulib_cmd *cmd, int rc);
int tcmu_handle_passthrough(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_unmap(struct tcmu_device *dev, struct tcmulib_cmd *origcmd);
int tcmu_handle_writesame(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_write_verify(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_xcopy(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_caw(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_flush(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_recv_copy_result(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_write(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_read(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_format_unit(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_stpg(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_rtpg(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_handle_inquiry(struct tcmu_device *dev, struct tcmulib_cmd *cmd);
int tcmu_dev_update_size(struct tcmu_device *dev, unsigned long new_size);
void tcmu_set_pending_ua(struct tcmu_device *dev, int ua);
int tcmu_handle_pending_ua(struct tcmulib_device *rdev, struct tcmulib_cmd *cmd);

#endif
