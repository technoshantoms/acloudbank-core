/*
 * Acloudbank
 */


#include <graphene/protocol/restriction.hpp>

namespace graphene { namespace protocol {

struct adder {
   size_t sum = 0;
   void operator()(const restriction& r) { sum += r.restriction_count(); }
   void operator()(const vector<restriction>& r) { sum += std::for_each(r.begin(), r.end(), adder()).sum; }
};

size_t restriction::restriction_count(const vector<restriction>& restrictions) {
   return std::for_each(restrictions.begin(), restrictions.end(), adder()).sum;
}

size_t restriction::restriction_count() const {
   if (argument.is_type<vector<restriction>>()) {
      const vector<restriction>& rs = argument.get<vector<restriction>>();
      return 1 + std::for_each(rs.begin(), rs.end(), adder()).sum;
   } else if (argument.is_type<vector<vector<restriction>>>()) {
      const vector<vector<restriction>>& rs = argument.get<vector<vector<restriction>>>();
      return 1 + std::for_each(rs.begin(), rs.end(), adder()).sum;
   } else if (argument.is_type<variant_assert_argument_type>()) {
      const variant_assert_argument_type& arg = argument.get<variant_assert_argument_type>();
      return 1 + std::for_each(arg.second.begin(), arg.second.end(), adder()).sum;
   }
   return 1;
}

} } // namespace graphene::protocol
