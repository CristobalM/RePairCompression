//
// Created by cristobal on 02-11-21.
//

#include "EntryPair.hpp"
namespace RePairCompression {

EntryPair::EntryPair(RePairCompression::Entry *first,
                     RePairCompression::Entry *second)
    : first(first), second(second) {}

} // namespace RePairCompression