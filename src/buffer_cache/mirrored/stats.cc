// Copyright 2010-2013 RethinkDB, all rights reserved.
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "buffer_cache/mirrored/stats.hpp"

mc_cache_stats_t::perfmon_cache_custom_t::perfmon_cache_custom_t()
    : block_size(0)
{
}

void *mc_cache_stats_t::perfmon_cache_custom_t::begin_stats() {
    return NULL;
}

void mc_cache_stats_t::perfmon_cache_custom_t::visit_stats(void *) {
}

scoped_ptr_t<perfmon_result_t>
mc_cache_stats_t::perfmon_cache_custom_t::end_stats(void *) {
    return make_scoped<perfmon_result_t>(strprintf("%" PRIu32, block_size));
}

mc_cache_stats_t::mc_cache_stats_t(perfmon_collection_t *parent)
    : cache_collection(),
      cache_membership(parent, &cache_collection, "cache"),
      pm_registered_snapshots(),
      pm_registered_snapshot_blocks(),
      pm_snapshots_per_transaction(secs_to_ticks(1), false),
      pm_cache_hits(),
      pm_cache_misses(),
      pm_bufs_acquiring(secs_to_ticks(1)),
      pm_bufs_held(secs_to_ticks(1)),
      pm_transactions_starting(secs_to_ticks(1)),
      pm_transactions_active(secs_to_ticks(1)),
      pm_transactions_committing(secs_to_ticks(1)),
      pm_flushes_locking(secs_to_ticks(10)),
      pm_flushes_writing(secs_to_ticks(10)),
      pm_flushes_preparing(secs_to_ticks(10)),
      pm_flushes_finalizing(secs_to_ticks(10)),
      pm_flushes_blocks(secs_to_ticks(10), true),
      pm_flushes_blocks_dirty(secs_to_ticks(10), true),
      pm_n_blocks_in_memory(),
      pm_n_blocks_dirty(),
      pm_n_blocks_total(),
      pm_n_blocks_evicted(),
      pm_block_size(),
      cache_collection_membership(&cache_collection,
          &pm_registered_snapshots, "registered_snapshots",
          &pm_registered_snapshot_blocks, "registered_snapshot_blocks",
          &pm_snapshots_per_transaction, "snapshots_per_transaction",
          &pm_cache_hits, "cache_hits",
          &pm_cache_misses, "cache_misses",
          &pm_bufs_acquiring, "bufs_acquiring",
          &pm_bufs_held, "bufs_held",
          &pm_transactions_starting, "transactions_starting",
          &pm_transactions_active, "transactions_active",
          &pm_transactions_committing, "transactions_committing",
          &pm_flushes_locking, "flushes_locking",
          &pm_flushes_writing, "flushes_writing",
          &pm_flushes_preparing, "flushes_preparing",
          &pm_flushes_finalizing, "flushes_finalizing",
          &pm_flushes_blocks, "flushes_blocks",
          &pm_flushes_blocks_dirty, "flushes_blocks_need_flush",
          &pm_n_blocks_in_memory, "blocks_in_memory",
          &pm_n_blocks_dirty, "blocks_dirty",
          &pm_n_blocks_total, "blocks_total",
          &pm_n_blocks_evicted, "blocks_evicted",
          &pm_block_size, "block_size",
          NULLPTR) { }


