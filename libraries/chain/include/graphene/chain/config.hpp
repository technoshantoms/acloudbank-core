/*
 * Acloudbank
 */
#pragma once

#include <graphene/protocol/config.hpp>

#include <string>

#define GRAPHENE_MIN_UNDO_HISTORY 10
#define GRAPHENE_MAX_UNDO_HISTORY 10000

#define GRAPHENE_MAX_NESTED_OBJECTS (200)

const std::string GRAPHENE_CURRENT_DB_VERSION = "20230906";

#define GRAPHENE_RECENTLY_MISSED_COUNT_INCREMENT             4
#define GRAPHENE_RECENTLY_MISSED_COUNT_DECREMENT             3

