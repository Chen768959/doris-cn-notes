// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "exec/tablet_sink.h"
#include "runtime/row_batch.h"

namespace doris {

namespace vectorized {
class VExprContext;
}

namespace stream_load {

class OlapTableSink;

// Write block data to Olap Table.
// When OlapTableSink::open() called, there will be a consumer thread running in the background.
// When you call VOlapTableSink::send(), you will be the producer who products pending batches.
// Join the consumer thread in close().
class VOlapTableSink : public OlapTableSink {
public:
    // Construct from thrift struct which is generated by FE.
    VOlapTableSink(ObjectPool* pool, const RowDescriptor& row_desc,
                   const std::vector<TExpr>& texprs, Status* status);

    Status init(const TDataSink& sink) override;
    // TODO: unify the code of prepare/open/close with result sink
    Status prepare(RuntimeState* state) override;

    Status open(RuntimeState* state) override;

    Status close(RuntimeState* state, Status close_status) override;
    using OlapTableSink::send;
    Status send(RuntimeState* state, vectorized::Block* block) override;

    size_t get_pending_bytes() const;
private:
    // make input data valid for OLAP table
    // return number of invalid/filtered rows.
    // invalid row number is set in Bitmap
    // set stop_processing is we want to stop the whole process now.
    Status _validate_data(RuntimeState* state, vectorized::Block* block, Bitmap* filter_bitmap,
                          int* filtered_rows, bool* stop_processing);

    // some output column of output expr may have different nullable property with dest slot desc
    // so here need to do the convert operation
    void _convert_to_dest_desc_block(vectorized::Block* block);

    VOlapTablePartitionParam* _vpartition = nullptr;
    std::vector<vectorized::VExprContext*> _output_vexpr_ctxs;
};

} // namespace stream_load
} // namespace doris
