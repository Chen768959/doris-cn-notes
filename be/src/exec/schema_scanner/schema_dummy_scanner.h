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

#ifndef DORIS_BE_SRC_QUERY_EXEC_SCHEMA_SCANNER_SCHEMA_DUMMY_SCANNER_H
#define DORIS_BE_SRC_QUERY_EXEC_SCHEMA_SCANNER_SCHEMA_DUMMY_SCANNER_H

#include "exec/schema_scanner.h"
#include "gen_cpp/FrontendService_types.h"

namespace doris {

class SchemaDummyScanner : public SchemaScanner {
public:
    SchemaDummyScanner();
    virtual ~SchemaDummyScanner();
    virtual Status start(RuntimeState* state = nullptr);
    virtual Status get_next_row(Tuple* tuple, MemPool* pool, bool* eos);

private:
    static SchemaScanner::ColumnDesc _s_dummy_columns[];
};

} // namespace doris

#endif
