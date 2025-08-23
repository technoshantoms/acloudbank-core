

/* This file contains forward declarations for externalized specializations of the create_predicate_function
 * template. Generate using the following shell code, and paste below.

FWD_FIELD_TYPES="share_type asset_id_type flat_set<asset_id_type> asset price"
FWD_FIELD_TYPES="$FWD_FIELD_TYPES string std::vector<char> time_point_sec"
FWD_FIELD_TYPES="$FWD_FIELD_TYPES account_id_type flat_set<account_id_type> public_key_type authority"
FWD_FIELD_TYPES="$FWD_FIELD_TYPES optional<authority>"
FWD_FIELD_TYPES="$FWD_FIELD_TYPES bool uint8_t uint16_t uint32_t unsigned_int extensions_type"

for T in $FWD_FIELD_TYPES; do
    echo "extern template"
    echo "object_restriction_predicate<$T> create_predicate_function( "
    echo "    restriction_function func, restriction_argument arg );"
done
 * ---------------- CUT ---------------- */

extern template
object_restriction_predicate<share_type> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<asset_id_type> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<flat_set<asset_id_type>> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<asset> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<price> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<string> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<std::vector<char>> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<time_point_sec> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<account_id_type> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<flat_set<account_id_type>> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<public_key_type> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<authority> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<optional<authority>> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<bool> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<uint8_t> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<uint16_t> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<uint32_t> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<unsigned_int> create_predicate_function(
    restriction_function func, restriction_argument arg );
extern template
object_restriction_predicate<extensions_type> create_predicate_function(
    restriction_function func, restriction_argument arg );
