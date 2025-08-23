/*
 * Acloudbank
 */

#pragma once

#include <graphene/protocol/restriction.hpp>
#include <graphene/protocol/operations.hpp>

#include <functional>

namespace graphene { namespace protocol {

/// A type describing the result of a restriction predicate
struct predicate_result {
   /// Whether or not the operation complied with the restrictions or not
   bool success = false;

   /// Enumeration of the general reasons a predicate may reject
   enum rejection_reason {
      predicate_was_false,
      null_optional,
      incorrect_variant_type
   };

   /// An indicator of what rejection occurred at a particular restriction -- either an index to a sub-restriction, a
   /// list of rejection results from the branches of a logical OR, or the immediate reason for rejection
   using rejection_indicator = static_variant<size_t, vector<predicate_result>, rejection_reason>;
   /// Failure indicators, ordered from the outermost restriction to the innermost (the location of the rejection)
   vector<rejection_indicator> rejection_path;

   static predicate_result Rejection(rejection_reason reason) { return {false, {reason}}; }
   static predicate_result Rejection(vector<predicate_result> branches) { return {false, {std::move(branches)}}; }
   static predicate_result Success() { return {true, {}}; }

   operator bool() const { return success; }

   /// Reverse the order of the rejection path. Returns a reference to this object
   predicate_result& reverse_path();
};

/// A restriction predicate is a function accepting an operation and returning a predicate_result
using restriction_predicate_function = std::function<predicate_result(const operation&)>;

/**
 * @brief get_restriction_predicate Get a predicate function for the supplied restriction
 * @param rs The restrictions to evaluate operations against
 * @param op_type The tag specifying which operation type the restrictions apply to
 * @return A predicate function which evaluates an operation to determine whether it complies with the restriction
 */
restriction_predicate_function get_restriction_predicate(vector<restriction> rs, operation::tag_type op_type);

} } // namespace graphene::protocol

FC_REFLECT_ENUM(graphene::protocol::predicate_result::rejection_reason,
                (predicate_was_false)(null_optional)(incorrect_variant_type))
FC_REFLECT_TYPENAME(graphene::protocol::predicate_result::rejection_indicator)
FC_REFLECT(graphene::protocol::predicate_result, (success)(rejection_path))
