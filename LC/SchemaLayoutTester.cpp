// // C++ program to illustrate the
// // iterators in vector
// #include <iostream>
// #include <vector>
// #include <string>
// #include <cstdint>
// #include <cassert>
//
// // Simplified type definitions
// using FieldId = uint16_t;
// using FieldOffset = int32_t;
// using Oid = uint32_t;
//
// // Type alignment macro
// #define TYPEALIGN(ALIGNVAL, LEN) \
//     (((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))
//
// #define MAXALIGN(LEN) TYPEALIGN(8, (LEN))
//
// // Simplified type IDs (you can adjust these)
// enum TypeIds {
//     TYP_INT2 = 21,
//     TYP_INT4 = 23,
//     TYP_VARCHAR = 1043,
//     TYP_CHAR = 1042,
//     TYP_DECIMAL = 1700
// };
//
// struct FieldInfo {
//     Oid m_typid;
//     uint64_t m_typparam;
//     int16_t m_typlen;        // -1 for varlen, >0 for fixed length
//     uint8_t m_typalign;      // alignment requirement
//     bool m_typbyref;         // pass by reference?
//     FieldId m_nullbit_id;    // -1 for non-nullable, >=0 for nullable
//     FieldOffset m_offset;    // computed offset or negative index
// };
//
// class SchemaLayoutTester {
// private:
//     std::vector<FieldInfo> m_field;
//     FieldOffset m_null_bitmap_begin;
//     FieldOffset m_varlen_end_array_begin;
//     FieldOffset m_varlen_payload_begin;
//     FieldId m_num_nonnullable_fixedlen_fields;
//     FieldId m_num_nullable_fixedlen_fields;
//     FieldId m_num_varlen_fields;
//     bool m_has_only_nonnullable_fixedlen_fields;
//
// public:
//     SchemaLayoutTester(const std::vector<Oid>& typids,
//                       const std::vector<uint64_t>& typparams,
//                       const std::vector<bool>& nullable) {
//         m_field.resize(typids.size());
//
//         for (size_t i = 0; i < typids.size(); ++i) {
//             m_field[i].m_typid = typids[i];
//             m_field[i].m_typparam = typparams[i];
//             m_field[i].m_nullbit_id = nullable[i] ? 0 : -1; // will be reassigned later
//             m_field[i].m_offset = 0;
//
//             // Set type properties based on type ID
//             switch (typids[i]) {
//                 case TYP_INT2:
//                     m_field[i].m_typlen = 2;
//                     m_field[i].m_typalign = 2;
//                     m_field[i].m_typbyref = false;
//                     break;
//                 case TYP_INT4:
//                     m_field[i].m_typlen = 4;
//                     m_field[i].m_typalign = 4;
//                     m_field[i].m_typbyref = false;
//                     break;
//                 case TYP_VARCHAR:
//                     m_field[i].m_typlen = -1; // variable length
//                     m_field[i].m_typalign = 1;
//                     m_field[i].m_typbyref = true;
//                     break;
//                 case TYP_CHAR:
//                     m_field[i].m_typlen = typparams[i]; // fixed length from param
//                     m_field[i].m_typalign = 1;
//                     m_field[i].m_typbyref = true;
//                     break;
//                 case TYP_DECIMAL:
//                     m_field[i].m_typlen = -1; // variable length
//                     m_field[i].m_typalign = 1;
//                     m_field[i].m_typbyref = true;
//                     break;
//                 default:
//                     std::cerr << "Unknown type ID: " << typids[i] << std::endl;
//                     break;
//             }
//         }
//     }
//
//     void ComputeLayout() {
//         FieldOffset off = 0;
//         FieldId num_fields = m_field.size();
//         FieldId num_nonnullable_fixedlen_fields = 0;
//         FieldId num_nullable_fixedlen_fields = 0;
//         FieldId num_varlen_fields = 0;
//         FieldId num_nullable_fields = 0;
//
//         std::cout << "\n=== COMPUTING SCHEMA LAYOUT ===\n";
//         std::cout << "Total fields: " << num_fields << "\n\n";
//
//         // Phase 1: Process all fields and categorize them
//         for (FieldId i = 0; i < num_fields; ++i) {
//             std::cout << "Field " << i << ": typid=" << m_field[i].m_typid
//                      << ", typlen=" << m_field[i].m_typlen
//                      << ", typalign=" << (int)m_field[i].m_typalign
//                      << ", nullable=" << (m_field[i].m_nullbit_id >= 0 ? "yes" : "no") << "\n";
//
//             if (m_field[i].m_typlen == -1) {
//                 // Variable-length field
//                 ++num_varlen_fields;
//                 m_field[i].m_offset = -num_varlen_fields; // negative index
//                 std::cout << "  -> Variable-length field, varlen_idx=" << (num_varlen_fields-1) << "\n";
//             } else if (m_field[i].m_nullbit_id >= 0) {
//                 // Nullable fixed-length field
//                 ++num_nullable_fixedlen_fields;
//                 m_field[i].m_offset = -num_nullable_fixedlen_fields; // negative index
//                 std::cout << "  -> Nullable fixed-length field\n";
//             } else {
//                 // Non-nullable fixed-length field - compute direct offset
//                 uint8_t align = m_field[i].m_typalign;
//                 off = TYPEALIGN(align, off);
//                 m_field[i].m_offset = off;
//                 off += m_field[i].m_typlen;
//                 ++num_nonnullable_fixedlen_fields;
//                 std::cout << "  -> Non-nullable fixed-length field, offset=" << m_field[i].m_offset << "\n";
//             }
//         }
//
//         m_num_nonnullable_fixedlen_fields = num_nonnullable_fixedlen_fields;
//         m_num_nullable_fixedlen_fields = num_nullable_fixedlen_fields;
//         m_num_varlen_fields = num_varlen_fields;
//
//         std::cout << "\nField counts:\n";
//         std::cout << "  Non-nullable fixed-length: " << num_nonnullable_fixedlen_fields << "\n";
//         std::cout << "  Nullable fixed-length: " << num_nullable_fixedlen_fields << "\n";
//         std::cout << "  Variable-length: " << num_varlen_fields << "\n";
//
//         // Check for fast path
//         if (num_nonnullable_fixedlen_fields == num_fields) {
//             off = MAXALIGN(off);
//             m_null_bitmap_begin = off;
//             m_varlen_end_array_begin = off;
//             m_varlen_payload_begin = off;
//             m_has_only_nonnullable_fixedlen_fields = true;
//             std::cout << "\nFast path: All fields are non-nullable fixed-length\n";
//             std::cout << "Final record size: " << off << " bytes\n";
//             return;
//         }
//
//         m_has_only_nonnullable_fixedlen_fields = false;
//
//         // Phase 2: Assign null bit IDs
//         for (FieldId i = 0; i < num_fields; ++i) {
//             if (m_field[i].m_nullbit_id >= 0) {
//                 m_field[i].m_nullbit_id = num_nullable_fields;
//                 ++num_nullable_fields;
//             }
//         }
//
//         // Phase 3: Compute layout sections
//         m_null_bitmap_begin = off;
//         off += (num_nullable_fields + 7) >> 3; // ceil(num_nullable_fields / 8)
//
//         off = TYPEALIGN(sizeof(FieldOffset), off);
//         m_varlen_end_array_begin = off;
//         off += sizeof(FieldOffset) * num_varlen_fields;
//         m_varlen_payload_begin = off;
//
//         std::cout << "\nLayout sections:\n";
//         std::cout << "  Fixed fields end at: " << m_null_bitmap_begin << "\n";
//         std::cout << "  Null bitmap: " << m_null_bitmap_begin << " (size: " << ((num_nullable_fields + 7) >> 3) << " bytes)\n";
//         std::cout << "  Varlen end array: " << m_varlen_end_array_begin << " (size: " << (sizeof(FieldOffset) * num_varlen_fields) << " bytes)\n";
//         std::cout << "  Varlen payload begins at: " << m_varlen_payload_begin << "\n";
//     }
//
//     void PrintDetailedLayout() {
//         std::cout << "\n=== DETAILED FIELD LAYOUT ===\n";
//         for (FieldId i = 0; i < m_field.size(); ++i) {
//             std::cout << "Field " << i << ":\n";
//             std::cout << "  Type ID: " << m_field[i].m_typid << " (";
//             switch (m_field[i].m_typid) {
//                 case TYP_INT2: std::cout << "INT2"; break;
//                 case TYP_INT4: std::cout << "INT4"; break;
//                 case TYP_VARCHAR: std::cout << "VARCHAR"; break;
//                 case TYP_CHAR: std::cout << "CHAR"; break;
//                 case TYP_DECIMAL: std::cout << "DECIMAL"; break;
//                 default: std::cout << "UNKNOWN"; break;
//             }
//             std::cout << ")\n";
//             std::cout << "  Type length: " << m_field[i].m_typlen << "\n";
//             std::cout << "  Type alignment: " << (int)m_field[i].m_typalign << "\n";
//             std::cout << "  Pass by reference: " << (m_field[i].m_typbyref ? "yes" : "no") << "\n";
//             std::cout << "  Nullable: " << (m_field[i].m_nullbit_id >= 0 ? "yes" : "no");
//             if (m_field[i].m_nullbit_id >= 0) {
//                 std::cout << " (null bit ID: " << m_field[i].m_nullbit_id << ")";
//             }
//             std::cout << "\n";
//             std::cout << "  Offset/Index: " << m_field[i].m_offset;
//             if (m_field[i].m_offset >= 0) {
//                 std::cout << " (direct offset in record)";
//             } else if (m_field[i].m_typlen == -1) {
//                 std::cout << " (varlen array index: " << (-m_field[i].m_offset - 1) << ")";
//             } else {
//                 std::cout << " (nullable field index: " << (-m_field[i].m_offset - 1) << ")";
//             }
//             std::cout << "\n\n";
//         }
//     }
//
//     void SimulateGetOffsetAndLength(FieldId field_id, const std::vector<int>& varlen_ends = {}) {
//         std::cout << "\n=== SIMULATING GetOffsetAndLength for field " << field_id << " ===\n";
//
//         if (field_id >= m_field.size()) {
//             std::cout << "ERROR: Invalid field ID\n";
//             return;
//         }
//
//         const FieldInfo &f = m_field[field_id];
//         std::cout << "Field info: typlen=" << f.m_typlen << ", offset=" << f.m_offset
//                  << ", nullbit_id=" << f.m_nullbit_id << ", typid=" << f.m_typid << "\n";
//
//         // Fixed-length fields
//         if (f.m_typlen > 0) {
//             if (f.m_nullbit_id < 0) {
//                 // Non-nullable fixed-length
//                 std::cout << "Non-nullable fixed-length field\n";
//                 std::cout << "Result: offset=" << f.m_offset << ", length=" << f.m_typlen << "\n";
//             } else {
//                 // Nullable fixed-length
//                 std::cout << "Nullable fixed-length field, nullbit_id=" << f.m_nullbit_id << "\n";
//
//                 // Check if schema has varlen fields
//                 bool has_varlen = (m_num_varlen_fields > 0);
//                 std::cout << "Schema has varlen fields: " << (has_varlen ? "yes" : "no") << "\n";
//
//                 if (has_varlen) {
//                     std::cout << "Nullable field in schema with varlen fields\n";
//
//                     // Find end of all varlen data (simulated)
//                     FieldOffset varlen_end = m_varlen_payload_begin;
//                     if (!varlen_ends.empty()) {
//                         for (int end : varlen_ends) {
//                             if (end > varlen_end) varlen_end = end;
//                         }
//                     }
//                     std::cout << "Varlen data ends at offset: " << varlen_end << "\n";
//
//                     // Place nullable fields after varlen data
//                     FieldOffset current_offset = varlen_end;
//                     if (f.m_typalign > 1) {
//                         FieldOffset old_offset = current_offset;
//                         current_offset = TYPEALIGN(f.m_typalign, current_offset);
//                         std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
//                     }
//
//                     // Add previous nullable fixed-length fields
//                     for (FieldId i = 0; i < field_id; ++i) {
//                         const FieldInfo &prev = m_field[i];
//                         if (prev.m_nullbit_id >= 0 && prev.m_nullbit_id < f.m_nullbit_id && prev.m_typlen > 0) {
//                             std::cout << "Adding previous nullable field " << i << " (size=" << prev.m_typlen << ")\n";
//                             current_offset += prev.m_typlen;
//                             if (f.m_typalign > 1) {
//                                 FieldOffset old_offset = current_offset;
//                                 current_offset = TYPEALIGN(f.m_typalign, current_offset);
//                                 std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
//                             }
//                         }
//                     }
//
//                     std::cout << "Result: offset=" << current_offset << ", length=" << f.m_typlen << "\n";
//                 } else {
//                     std::cout << "Nullable field in nullable-only schema\n";
//                     FieldOffset current_offset = m_varlen_payload_begin;
//                     std::cout << "Starting at varlen_payload_begin: " << current_offset << "\n";
//
//                     for (FieldId i = 0; i < field_id; ++i) {
//                         const FieldInfo &prev = m_field[i];
//                         if (prev.m_nullbit_id >= 0 && prev.m_nullbit_id < f.m_nullbit_id) {
//                             std::cout << "Adding previous nullable field " << i << " (size=" << prev.m_typlen << ")\n";
//                             current_offset += prev.m_typlen;
//                             if (f.m_typalign > 1) {
//                                 FieldOffset old_offset = current_offset;
//                                 current_offset = TYPEALIGN(f.m_typalign, current_offset);
//                                 std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
//                             }
//                         }
//                     }
//
//                     std::cout << "Result: offset=" << current_offset << ", length=" << f.m_typlen << "\n";
//                 }
//             }
//         }
//         // Variable-length fields
//         else if (f.m_typlen < 0) {
//             int varlen_idx = -f.m_offset - 1;
//             std::cout << "Variable-length field, varlen_idx=" << varlen_idx << "\n";
//
//             if (varlen_idx < varlen_ends.size()) {
//                 FieldOffset absolute_end = varlen_ends[varlen_idx];
//                 std::cout << "end_array[" << varlen_idx << "]=" << absolute_end << "\n";
//
//                 FieldOffset start;
//                 if (varlen_idx == 0) {
//                     start = m_varlen_payload_begin;
//                     std::cout << "First varlen field, start=" << start << "\n";
//                 } else {
//                     FieldOffset prev_end = varlen_ends[varlen_idx - 1];
//                     std::cout << "Previous varlen end=" << prev_end << "\n";
//                     if (f.m_typalign > 1) {
//                         start = TYPEALIGN(f.m_typalign, prev_end);
//                         std::cout << "Applied alignment " << (int)f.m_typalign << ": " << prev_end << " -> " << start << "\n";
//                     } else {
//                         start = prev_end;
//                     }
//                 }
//
//                 FieldOffset data_length = absolute_end - start;
//                 std::cout << "Result: offset=" << start << ", length=" << data_length << "\n";
//             } else {
//                 std::cout << "Need varlen_ends array to compute actual offset/length\n";
//             }
//         }
//     }
// };
//
// // Test various schema configurations
// void testSchema1() {
//     std::cout << "\n" << std::string(60, '=') << "\n";
//     std::cout << "TEST 1: All non-nullable fixed-length fields\n";
//     std::cout << "Schema: INT4, INT2, INT4\n";
//     std::cout << std::string(60, '=') << "\n";
//
//     SchemaLayoutTester schema({TYP_INT4, TYP_INT2, TYP_INT4},
//                              {0, 0, 0},
//                              {false, false, false});
//     schema.ComputeLayout();
//     schema.PrintDetailedLayout();
//     schema.SimulateGetOffsetAndLength(0);
//     schema.SimulateGetOffsetAndLength(1);
//     schema.SimulateGetOffsetAndLength(2);
// }
//
// void testSchema2() {
//     std::cout << "\n" << std::string(60, '=') << "\n";
//     std::cout << "TEST 2: Mixed nullable and non-nullable fixed-length\n";
//     std::cout << "Schema: INT4 NOT NULL, INT2 NULLABLE, INT4 NOT NULL\n";
//     std::cout << std::string(60, '=') << "\n";
//
//     SchemaLayoutTester schema({TYP_INT4, TYP_INT2, TYP_INT4},
//                              {0, 0, 0},
//                              {false, true, false});
//     schema.ComputeLayout();
//     schema.PrintDetailedLayout();
//     schema.SimulateGetOffsetAndLength(0);
//     schema.SimulateGetOffsetAndLength(1);
//     schema.SimulateGetOffsetAndLength(2);
// }
//
// void testSchema3() {
//     std::cout << "\n" << std::string(60, '=') << "\n";
//     std::cout << "TEST 3: Variable-length fields\n";
//     std::cout << "Schema: INT4 NOT NULL, VARCHAR(100) NOT NULL, INT2 NOT NULL\n";
//     std::cout << std::string(60, '=') << "\n";
//
//     SchemaLayoutTester schema({TYP_INT4, TYP_VARCHAR, TYP_INT2},
//                              {0, 100, 0},
//                              {false, false, false});
//     schema.ComputeLayout();
//     schema.PrintDetailedLayout();
//     schema.SimulateGetOffsetAndLength(0);
//
//     // Simulate varlen field with some sample end offsets
//     std::vector<int> varlen_ends = {25}; // VARCHAR ends at offset 25
//     schema.SimulateGetOffsetAndLength(1, varlen_ends);
//     schema.SimulateGetOffsetAndLength(2);
// }
//
// void testSchema4() {
//     std::cout << "\n" << std::string(60, '=') << "\n";
//     std::cout << "TEST 4: Complex mixed schema (your test case)\n";
//     std::cout << "Schema: INT2 NULLABLE, VARCHAR(100) NOT NULL, INT4 NOT NULL, INT2 NOT NULL, VARCHAR(2) NULLABLE, INT4 NULLABLE\n";
//     std::cout << std::string(60, '=') << "\n";
//
//     SchemaLayoutTester schema({TYP_INT2, TYP_VARCHAR, TYP_INT4, TYP_INT2, TYP_VARCHAR, TYP_INT4},
//                              {0, 100, 0, 0, 2, 0},
//                              {true, false, false, false, true, true});
//     schema.ComputeLayout();
//     schema.PrintDetailedLayout();
//
//     // Simulate with some sample varlen end offsets
//     std::vector<int> varlen_ends = {25, 27}; // VARCHAR(100) ends at 25, VARCHAR(2) ends at 27
//
//     for (FieldId i = 0; i < 6; ++i) {
//         schema.SimulateGetOffsetAndLength(i, varlen_ends);
//     }
// }
//
// void testSchema5() {
//     std::cout << "\n" << std::string(60, '=') << "\n";
//     std::cout << "TEST 5: CREATE TABLE A schema\n";
//     std::cout << "Schema: CHAR(2) NULLABLE, VARCHAR(100) NOT NULL, CHAR(5) NOT NULL, INT2 NOT NULL, VARCHAR(2) NULLABLE, INT4 NULLABLE\n";
//     std::cout << std::string(60, '=') << "\n";
//
//     SchemaLayoutTester schema({TYP_CHAR, TYP_VARCHAR, TYP_CHAR, TYP_INT2, TYP_VARCHAR, TYP_INT4},
//                              {2, 100, 5, 0, 2, 0},
//                              {true, false, false, false, true, true});
//     schema.ComputeLayout();
//     schema.PrintDetailedLayout();
//
//     // Simulate with some sample varlen end offsets
//     // VARCHAR(100) with "hello world" (11 chars) -> ends at offset 21 (10 + 11)
//     // VARCHAR(2) with "xy" (2 chars) -> ends at offset 23 (21 + 2)
//     std::vector<int> varlen_ends = {21, 23};
//
//     std::cout << "\n--- Simulating GetOffsetAndLength for all fields ---\n";
//     for (FieldId i = 0; i < 6; ++i) {
//         schema.SimulateGetOffsetAndLength(i, varlen_ends);
//     }
//
//     std::cout << "\n--- Expected vs Computed Analysis ---\n";
//     std::cout << "Based on the schema layout:\n";
//     std::cout << "- Non-nullable fixed fields: f3 CHAR(5), f4 INT2\n";
//     std::cout << "- Variable-length fields: f2 VARCHAR(100), f5 VARCHAR(2)\n";
//     std::cout << "- Nullable fixed fields: f1 CHAR(2), f6 INT4\n";
//     std::cout << "\nField order in record:\n";
//     std::cout << "1. f3 CHAR(5) at offset 0-4\n";
//     std::cout << "2. f4 INT2 at offset 6 (aligned to 2-byte boundary)\n";
//     std::cout << "3. Null bitmap at offset 8 (1 byte for 3 nullable fields)\n";
//     std::cout << "4. Varlen end array at offset 12 (8 bytes for 2 varlen fields)\n";
//     std::cout << "5. Varlen payload starts at offset 20\n";
//     std::cout << "6. f2 VARCHAR(100) data at offset 20\n";
//     std::cout << "7. f5 VARCHAR(2) data follows f2\n";
//     std::cout << "8. f1 CHAR(2) after varlen data (if not null)\n";
//     std::cout << "9. f6 INT4 after f1 with proper alignment (if not null)\n";
// }
//
// int main() {
//     std::cout << "Schema Layout Tester\n";
//     std::cout << "This tool helps understand how different field types are laid out in memory\n";
//
//     // testSchema1();
//     // testSchema2();
//     // testSchema3();
//     // testSchema4();
//     testSchema5();
//
//     return 0;
// }



#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cassert>
#include <cstdio>

// Simplified type definitions
using FieldId = uint16_t;
using FieldOffset = int32_t;
using Oid = uint32_t;

// Type alignment macro
#define TYPEALIGN(ALIGNVAL, LEN) \
    (((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define MAXALIGN(LEN) TYPEALIGN(8, (LEN))

// Simplified type IDs (you can adjust these)
enum TypeIds {
    TYP_INT2 = 21,
    TYP_INT4 = 23,
    TYP_VARCHAR = 1043,
    TYP_CHAR = 1042,
    TYP_DECIMAL = 1700
};

struct FieldInfo {
    Oid m_typid;
    uint64_t m_typparam;
    int16_t m_typlen;        // -1 for varlen, >0 for fixed length
    uint8_t m_typalign;      // alignment requirement
    bool m_typbyref;         // pass by reference?
    FieldId m_nullbit_id;    // -1 for non-nullable, >=0 for nullable
    FieldOffset m_offset;    // computed offset or negative index
};

class SchemaLayoutTester {
private:
    std::vector<FieldInfo> m_field;
    FieldOffset m_null_bitmap_begin;
    FieldOffset m_varlen_end_array_begin;
    FieldOffset m_varlen_payload_begin;
    FieldId m_num_nonnullable_fixedlen_fields;
    FieldId m_num_nullable_fixedlen_fields;
    FieldId m_num_varlen_fields;
    bool m_has_only_nonnullable_fixedlen_fields;

    int GetNullableFieldCount() const {
        int count = 0;
        for (const auto& f : m_field) {
            if (f.m_nullbit_id >= 0) count++;
        }
        return count;
    }

public:
    SchemaLayoutTester(const std::vector<Oid>& typids,
                      const std::vector<uint64_t>& typparams,
                      const std::vector<bool>& nullable) {
        m_field.resize(typids.size());

        for (size_t i = 0; i < typids.size(); ++i) {
            m_field[i].m_typid = typids[i];
            m_field[i].m_typparam = typparams[i];
            m_field[i].m_nullbit_id = nullable[i] ? 0 : -1; // will be reassigned later
            m_field[i].m_offset = 0;

            // Set type properties based on type ID
            switch (typids[i]) {
                case TYP_INT2:
                    m_field[i].m_typlen = 2;
                    m_field[i].m_typalign = 2;
                    m_field[i].m_typbyref = false;
                    break;
                case TYP_INT4:
                    m_field[i].m_typlen = 4;
                    m_field[i].m_typalign = 4;
                    m_field[i].m_typbyref = false;
                    break;
                case TYP_VARCHAR:
                    m_field[i].m_typlen = -1; // variable length
                    m_field[i].m_typalign = 1;
                    m_field[i].m_typbyref = true;
                    break;
                case TYP_CHAR:
                    m_field[i].m_typlen = typparams[i]; // fixed length from param
                    m_field[i].m_typalign = 1;
                    m_field[i].m_typbyref = true;
                    break;
                case TYP_DECIMAL:
                    m_field[i].m_typlen = -1; // variable length
                    m_field[i].m_typalign = 1;
                    m_field[i].m_typbyref = true;
                    break;
                default:
                    std::cerr << "Unknown type ID: " << typids[i] << std::endl;
                    break;
            }
        }
    }

    void ComputeLayout() {
        FieldOffset off = 0;
        FieldId num_fields = m_field.size();
        FieldId num_nonnullable_fixedlen_fields = 0;
        FieldId num_nullable_fixedlen_fields = 0;
        FieldId num_varlen_fields = 0;
        FieldId num_nullable_fields = 0;

        std::cout << "\n=== COMPUTING SCHEMA LAYOUT ===\n";
        std::cout << "Total fields: " << num_fields << "\n\n";

        // Phase 1: Process all fields and categorize them
        for (FieldId i = 0; i < num_fields; ++i) {
            std::cout << "Field " << i << ": typid=" << m_field[i].m_typid
                     << ", typlen=" << m_field[i].m_typlen
                     << ", typalign=" << (int)m_field[i].m_typalign
                     << ", nullable=" << (m_field[i].m_nullbit_id >= 0 ? "yes" : "no") << "\n";

            if (m_field[i].m_typlen == -1) {
                // Variable-length field
                ++num_varlen_fields;
                m_field[i].m_offset = -num_varlen_fields; // negative index
                std::cout << "  -> Variable-length field, varlen_idx=" << (num_varlen_fields-1) << "\n";
            } else if (m_field[i].m_nullbit_id >= 0) {
                // Nullable fixed-length field
                ++num_nullable_fixedlen_fields;
                m_field[i].m_offset = -num_nullable_fixedlen_fields; // negative index
                std::cout << "  -> Nullable fixed-length field\n";
            } else {
                // Non-nullable fixed-length field - compute direct offset
                uint8_t align = m_field[i].m_typalign;
                off = TYPEALIGN(align, off);
                m_field[i].m_offset = off;
                off += m_field[i].m_typlen;
                ++num_nonnullable_fixedlen_fields;
                std::cout << "  -> Non-nullable fixed-length field, offset=" << m_field[i].m_offset << "\n";
            }
        }

        m_num_nonnullable_fixedlen_fields = num_nonnullable_fixedlen_fields;
        m_num_nullable_fixedlen_fields = num_nullable_fixedlen_fields;
        m_num_varlen_fields = num_varlen_fields;

        std::cout << "\nField counts:\n";
        std::cout << "  Non-nullable fixed-length: " << num_nonnullable_fixedlen_fields << "\n";
        std::cout << "  Nullable fixed-length: " << num_nullable_fixedlen_fields << "\n";
        std::cout << "  Variable-length: " << num_varlen_fields << "\n";

        // Check for fast path
        if (num_nonnullable_fixedlen_fields == num_fields) {
            off = MAXALIGN(off);
            m_null_bitmap_begin = off;
            m_varlen_end_array_begin = off;
            m_varlen_payload_begin = off;
            m_has_only_nonnullable_fixedlen_fields = true;
            std::cout << "\nFast path: All fields are non-nullable fixed-length\n";
            std::cout << "Final record size: " << off << " bytes\n";
            return;
        }

        m_has_only_nonnullable_fixedlen_fields = false;

        // Phase 2: Assign null bit IDs
        for (FieldId i = 0; i < num_fields; ++i) {
            if (m_field[i].m_nullbit_id >= 0) {
                m_field[i].m_nullbit_id = num_nullable_fields;
                ++num_nullable_fields;
            }
        }

        // Phase 3: Compute layout sections
        m_null_bitmap_begin = off;
        off += (num_nullable_fields + 7) >> 3; // ceil(num_nullable_fields / 8)

        off = TYPEALIGN(sizeof(FieldOffset), off);
        m_varlen_end_array_begin = off;
        off += sizeof(FieldOffset) * num_varlen_fields;
        m_varlen_payload_begin = off;

        std::cout << "\nLayout sections:\n";
        std::cout << "  Fixed fields end at: " << m_null_bitmap_begin << "\n";
        std::cout << "  Null bitmap: " << m_null_bitmap_begin << " (size: " << ((num_nullable_fields + 7) >> 3) << " bytes)\n";
        std::cout << "  Varlen end array: " << m_varlen_end_array_begin << " (size: " << (sizeof(FieldOffset) * num_varlen_fields) << " bytes)\n";
        std::cout << "  Varlen payload begins at: " << m_varlen_payload_begin << "\n";
    }

    void PrintMemoryLayout(const std::vector<int>& varlen_ends = {}) {
        std::cout << "\n=== VISUAL MEMORY LAYOUT ===\n";

        // Calculate total record size estimate
        int estimated_size = m_varlen_payload_begin;
        if (!varlen_ends.empty()) {
            for (int end : varlen_ends) {
                if (end > estimated_size) estimated_size = end;
            }
        }
        // Add space for nullable fixed fields (rough estimate)
        estimated_size += m_num_nullable_fixedlen_fields * 8; // conservative estimate

        std::vector<char> layout(estimated_size, '.');
        std::vector<std::string> labels(estimated_size, "");

        // Mark fixed-length non-nullable fields
        for (FieldId i = 0; i < m_field.size(); ++i) {
            const FieldInfo& f = m_field[i];
            if (f.m_typlen > 0 && f.m_nullbit_id < 0) {
                // Non-nullable fixed field
                for (int j = f.m_offset; j < f.m_offset + f.m_typlen && j < (int)layout.size(); ++j) {
                    layout[j] = 'F';
                    if (j == f.m_offset) {
                        labels[j] = "f" + std::to_string(i);
                    }
                }
            }
        }

        // Mark null bitmap
        int null_bitmap_size = (GetNullableFieldCount() + 7) >> 3;
        for (int j = m_null_bitmap_begin; j < m_null_bitmap_begin + null_bitmap_size && j < (int)layout.size(); ++j) {
            layout[j] = 'N';
            if (j == m_null_bitmap_begin) {
                labels[j] = "null_bmp";
            }
        }

        // Mark varlen end array
        int varlen_array_size = sizeof(FieldOffset) * m_num_varlen_fields;
        for (int j = m_varlen_end_array_begin; j < m_varlen_end_array_begin + varlen_array_size && j < (int)layout.size(); ++j) {
            layout[j] = 'E';
            if (j == m_varlen_end_array_begin) {
                labels[j] = "varlen_ends";
            }
        }

        // Mark varlen payload areas
        if (!varlen_ends.empty()) {
            int start = m_varlen_payload_begin;
            int varlen_field_idx = 0;

            for (FieldId i = 0; i < m_field.size() && varlen_field_idx < (int)varlen_ends.size(); ++i) {
                if (m_field[i].m_typlen == -1) {
                    int end = varlen_ends[varlen_field_idx];
                    for (int j = start; j < end && j < (int)layout.size(); ++j) {
                        layout[j] = 'V';
                        if (j == start) {
                            labels[j] = "f" + std::to_string(i) + "_data";
                        }
                    }
                    start = end;
                    varlen_field_idx++;
                }
            }
        }

        // Print the layout
        std::cout << "Byte layout (each character = 1 byte):\n";
        std::cout << "F=Fixed field, N=Null bitmap, E=End array, V=Varlen data, .=Padding/Unused\n\n";

        // Print in rows of 20 bytes
        for (int row = 0; row < (estimated_size + 19) / 20; ++row) {
            int start_byte = row * 20;
            int end_byte = std::min(start_byte + 20, (int)layout.size());

            // Print byte numbers header
            printf("%3d: ", start_byte);
            for (int i = start_byte; i < end_byte; ++i) {
                printf("%c", layout[i]);
            }
            printf("\n");

            // Print labels if any exist in this row
            bool has_labels = false;
            for (int i = start_byte; i < end_byte; ++i) {
                if (!labels[i].empty()) {
                    has_labels = true;
                    break;
                }
            }

            if (has_labels) {
                printf("     ");
                for (int i = start_byte; i < end_byte; ++i) {
                    if (!labels[i].empty()) {
                        printf("^");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n     ");

                for (int i = start_byte; i < end_byte; ++i) {
                    if (!labels[i].empty()) {
                        printf("%s", labels[i].c_str());
                        // Move to next position that doesn't have a label
                        int skip = labels[i].length() - 1;
                        while (skip > 0 && i + 1 < end_byte) {
                            i++;
                            skip--;
                        }
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
            printf("\n");
        }

        std::cout << "Layout sections:\n";
        std::cout << "  Fixed fields end: " << m_null_bitmap_begin << "\n";
        std::cout << "  Null bitmap: " << m_null_bitmap_begin << " - " << (m_varlen_end_array_begin - 1) << "\n";
        std::cout << "  Varlen end array: " << m_varlen_end_array_begin << " - " << (m_varlen_payload_begin - 1) << "\n";
        std::cout << "  Varlen payload: " << m_varlen_payload_begin << "+\n";
    }

    void PrintDetailedLayout() {
        std::cout << "\n=== DETAILED FIELD LAYOUT ===\n";
        for (FieldId i = 0; i < m_field.size(); ++i) {
            std::cout << "Field " << i << ":\n";
            std::cout << "  Type ID: " << m_field[i].m_typid << " (";
            switch (m_field[i].m_typid) {
                case TYP_INT2: std::cout << "INT2"; break;
                case TYP_INT4: std::cout << "INT4"; break;
                case TYP_VARCHAR: std::cout << "VARCHAR"; break;
                case TYP_CHAR: std::cout << "CHAR"; break;
                case TYP_DECIMAL: std::cout << "DECIMAL"; break;
                default: std::cout << "UNKNOWN"; break;
            }
            std::cout << ")\n";
            std::cout << "  Type length: " << m_field[i].m_typlen << "\n";
            std::cout << "  Type alignment: " << (int)m_field[i].m_typalign << "\n";
            std::cout << "  Pass by reference: " << (m_field[i].m_typbyref ? "yes" : "no") << "\n";
            std::cout << "  Nullable: " << (m_field[i].m_nullbit_id >= 0 ? "yes" : "no");
            if (m_field[i].m_nullbit_id >= 0) {
                std::cout << " (null bit ID: " << m_field[i].m_nullbit_id << ")";
            }
            std::cout << "\n";
            std::cout << "  Offset/Index: " << m_field[i].m_offset;
            if (m_field[i].m_offset >= 0) {
                std::cout << " (direct offset in record)";
            } else if (m_field[i].m_typlen == -1) {
                std::cout << " (varlen array index: " << (-m_field[i].m_offset - 1) << ")";
            } else {
                std::cout << " (nullable field index: " << (-m_field[i].m_offset - 1) << ")";
            }
            std::cout << "\n\n";
        }
    }

    void SimulateGetOffsetAndLength(FieldId field_id, const std::vector<int>& varlen_ends = {}) {
        std::cout << "\n=== SIMULATING GetOffsetAndLength for field " << field_id << " ===\n";

        if (field_id >= m_field.size()) {
            std::cout << "ERROR: Invalid field ID\n";
            return;
        }

        const FieldInfo &f = m_field[field_id];
        std::cout << "Field info: typlen=" << f.m_typlen << ", offset=" << f.m_offset
                 << ", nullbit_id=" << f.m_nullbit_id << ", typid=" << f.m_typid << "\n";

        // Fixed-length fields
        if (f.m_typlen > 0) {
            if (f.m_nullbit_id < 0) {
                // Non-nullable fixed-length
                std::cout << "Non-nullable fixed-length field\n";
                std::cout << "Result: offset=" << f.m_offset << ", length=" << f.m_typlen << "\n";
            } else {
                // Nullable fixed-length
                std::cout << "Nullable fixed-length field, nullbit_id=" << f.m_nullbit_id << "\n";

                // Check if schema has varlen fields
                bool has_varlen = (m_num_varlen_fields > 0);
                std::cout << "Schema has varlen fields: " << (has_varlen ? "yes" : "no") << "\n";

                if (has_varlen) {
                    std::cout << "Nullable field in schema with varlen fields\n";

                    // Find end of all varlen data (simulated)
                    FieldOffset varlen_end = m_varlen_payload_begin;
                    if (!varlen_ends.empty()) {
                        for (int end : varlen_ends) {
                            if (end > varlen_end) varlen_end = end;
                        }
                    }
                    std::cout << "Varlen data ends at offset: " << varlen_end << "\n";

                    // Place nullable fields after varlen data
                    FieldOffset current_offset = varlen_end;
                    if (f.m_typalign > 1) {
                        FieldOffset old_offset = current_offset;
                        current_offset = TYPEALIGN(f.m_typalign, current_offset);
                        std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
                    }

                    // Add previous nullable fixed-length fields
                    for (FieldId i = 0; i < field_id; ++i) {
                        const FieldInfo &prev = m_field[i];
                        if (prev.m_nullbit_id >= 0 && prev.m_nullbit_id < f.m_nullbit_id && prev.m_typlen > 0) {
                            std::cout << "Adding previous nullable field " << i << " (size=" << prev.m_typlen << ")\n";
                            current_offset += prev.m_typlen;
                            if (f.m_typalign > 1) {
                                FieldOffset old_offset = current_offset;
                                current_offset = TYPEALIGN(f.m_typalign, current_offset);
                                std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
                            }
                        }
                    }

                    std::cout << "Result: offset=" << current_offset << ", length=" << f.m_typlen << "\n";
                } else {
                    std::cout << "Nullable field in nullable-only schema\n";
                    FieldOffset current_offset = m_varlen_payload_begin;
                    std::cout << "Starting at varlen_payload_begin: " << current_offset << "\n";

                    for (FieldId i = 0; i < field_id; ++i) {
                        const FieldInfo &prev = m_field[i];
                        if (prev.m_nullbit_id >= 0 && prev.m_nullbit_id < f.m_nullbit_id) {
                            std::cout << "Adding previous nullable field " << i << " (size=" << prev.m_typlen << ")\n";
                            current_offset += prev.m_typlen;
                            if (f.m_typalign > 1) {
                                FieldOffset old_offset = current_offset;
                                current_offset = TYPEALIGN(f.m_typalign, current_offset);
                                std::cout << "Applied alignment " << (int)f.m_typalign << ": " << old_offset << " -> " << current_offset << "\n";
                            }
                        }
                    }

                    std::cout << "Result: offset=" << current_offset << ", length=" << f.m_typlen << "\n";
                }
            }
        }
        // Variable-length fields
        else if (f.m_typlen < 0) {
            int varlen_idx = -f.m_offset - 1;
            std::cout << "Variable-length field, varlen_idx=" << varlen_idx << "\n";

            if (varlen_idx < (int)varlen_ends.size()) {
                FieldOffset absolute_end = varlen_ends[varlen_idx];
                std::cout << "end_array[" << varlen_idx << "]=" << absolute_end << "\n";

                FieldOffset start;
                if (varlen_idx == 0) {
                    start = m_varlen_payload_begin;
                    std::cout << "First varlen field, start=" << start << "\n";
                } else {
                    FieldOffset prev_end = varlen_ends[varlen_idx - 1];
                    std::cout << "Previous varlen end=" << prev_end << "\n";
                    if (f.m_typalign > 1) {
                        start = TYPEALIGN(f.m_typalign, prev_end);
                        std::cout << "Applied alignment " << (int)f.m_typalign << ": " << prev_end << " -> " << start << "\n";
                    } else {
                        start = prev_end;
                    }
                }

                FieldOffset data_length = absolute_end - start;
                std::cout << "Result: offset=" << start << ", length=" << data_length << "\n";
            } else {
                std::cout << "Need varlen_ends array to compute actual offset/length\n";
            }
        }
    }
};

// Test various schema configurations
void testSchema1() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEST 1: All non-nullable fixed-length fields\n";
    std::cout << "Schema: INT4, INT2, INT4\n";
    std::cout << std::string(60, '=') << "\n";

    SchemaLayoutTester schema({TYP_INT4, TYP_INT2, TYP_INT4},
                             {0, 0, 0},
                             {false, false, false});
    schema.ComputeLayout();
    schema.PrintDetailedLayout();
    schema.PrintMemoryLayout();
    schema.SimulateGetOffsetAndLength(0);
    schema.SimulateGetOffsetAndLength(1);
    schema.SimulateGetOffsetAndLength(2);
}

void testSchema2() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEST 2: Mixed nullable and non-nullable fixed-length\n";
    std::cout << "Schema: INT4 NOT NULL, INT2 NULLABLE, INT4 NOT NULL\n";
    std::cout << std::string(60, '=') << "\n";

    SchemaLayoutTester schema({TYP_INT4, TYP_INT2, TYP_INT4},
                             {0, 0, 0},
                             {false, true, false});
    schema.ComputeLayout();
    schema.PrintDetailedLayout();
    schema.PrintMemoryLayout();
    schema.SimulateGetOffsetAndLength(0);
    schema.SimulateGetOffsetAndLength(1);
    schema.SimulateGetOffsetAndLength(2);
}

void testSchema3() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEST 3: Variable-length fields\n";
    std::cout << "Schema: INT4 NOT NULL, VARCHAR(100) NOT NULL, INT2 NOT NULL\n";
    std::cout << std::string(60, '=') << "\n";

    SchemaLayoutTester schema({TYP_INT4, TYP_VARCHAR, TYP_INT2},
                             {0, 100, 0},
                             {false, false, false});
    schema.ComputeLayout();
    schema.PrintDetailedLayout();

    // Simulate varlen field with some sample end offsets
    std::vector<int> varlen_ends = {25}; // VARCHAR ends at offset 25
    schema.PrintMemoryLayout(varlen_ends);
    schema.SimulateGetOffsetAndLength(0);
    schema.SimulateGetOffsetAndLength(1, varlen_ends);
    schema.SimulateGetOffsetAndLength(2);
}

void testSchema4() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEST 4: Complex mixed schema (your test case)\n";
    std::cout << "Schema: INT2 NULLABLE, VARCHAR(100) NOT NULL, INT4 NOT NULL, INT2 NOT NULL, VARCHAR(2) NULLABLE, INT4 NULLABLE\n";
    std::cout << std::string(60, '=') << "\n";

    SchemaLayoutTester schema({TYP_INT2, TYP_VARCHAR, TYP_INT4, TYP_INT2, TYP_VARCHAR, TYP_INT4},
                             {0, 100, 0, 0, 2, 0},
                             {true, false, false, false, true, true});
    schema.ComputeLayout();
    schema.PrintDetailedLayout();

    // Simulate with some sample varlen end offsets
    std::vector<int> varlen_ends = {25, 27}; // VARCHAR(100) ends at 25, VARCHAR(2) ends at 27
    schema.PrintMemoryLayout(varlen_ends);

    for (FieldId i = 0; i < 6; ++i) {
        schema.SimulateGetOffsetAndLength(i, varlen_ends);
    }
}

void testSchema5() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "TEST 5: CREATE TABLE A schema\n";
    std::cout << "Schema: CHAR(2) NULLABLE, VARCHAR(100) NOT NULL, CHAR(5) NOT NULL, INT2 NOT NULL, VARCHAR(2) NULLABLE, INT4 NULLABLE\n";
    std::cout << std::string(60, '=') << "\n";

    SchemaLayoutTester schema({TYP_CHAR, TYP_VARCHAR, TYP_CHAR, TYP_INT2, TYP_VARCHAR, TYP_INT4},
                             {2, 100, 5, 0, 2, 0},
                             {true, false, false, false, true, true});
    schema.ComputeLayout();
    schema.PrintDetailedLayout();

    // Simulate with some sample varlen end offsets
    // VARCHAR(100) with "hello world" (11 chars) -> ends at offset 31 (20 + 11)
    // VARCHAR(2) with "xy" (2 chars) -> ends at offset 33 (31 + 2)
    std::vector<int> varlen_ends = {31, 33};
    schema.PrintMemoryLayout(varlen_ends);

    std::cout << "\n--- Simulating GetOffsetAndLength for all fields ---\n";
    for (FieldId i = 0; i < 6; ++i) {
        schema.SimulateGetOffsetAndLength(i, varlen_ends);
    }

    std::cout << "\n--- Expected Record Layout Analysis ---\n";
    std::cout << "Based on the visual layout above:\n";
    std::cout << "- Non-nullable fixed fields: f2 CHAR(5) at 0-4, f3 INT2 at 6-7\n";
    std::cout << "- Null bitmap: 1 byte at offset 8 (3 nullable fields: f0,f4,f5)\n";
    std::cout << "- Varlen end array: 8 bytes at offset 12-19 (2 varlen fields: f1,f4)\n";
    std::cout << "- Varlen payload: starts at offset 20\n";
    std::cout << "  * f1 VARCHAR(100) data: 20-30 ('hello world')\n";
    std::cout << "  * f4 VARCHAR(2) data: 31-32 ('xy')\n";
    std::cout << "- Nullable fixed fields follow varlen data:\n";
    std::cout << "  * f0 CHAR(2): at offset 33-34 (if not null)\n";
    std::cout << "  * f5 INT4: at offset 36-39 (if not null, 4-byte aligned)\n";

    std::cout << "\nField access offsets when all fields are non-null:\n";
    std::cout << "f0 (CHAR(2)):    offset=33, length=2\n";
    std::cout << "f1 (VARCHAR):    offset=20, length=11\n";
    std::cout << "f2 (CHAR(5)):    offset=0,  length=5\n";
    std::cout << "f3 (INT2):       offset=6,  length=2\n";
    std::cout << "f4 (VARCHAR):    offset=31, length=2\n";
    std::cout << "f5 (INT4):       offset=36, length=4\n";
}

int main() {
    std::cout << "Schema Layout Tester\n";
    std::cout << "This tool helps understand how different field types are laid out in memory\n";

    // testSchema1();
    // testSchema2();
    // testSchema3();
    // testSchema4();
    testSchema5();

    return 0;
}

// g++ -std=c++11 SchemaLayoutTester.cpp -o SchemaLayoutTester
// ./SchemaLayoutTester