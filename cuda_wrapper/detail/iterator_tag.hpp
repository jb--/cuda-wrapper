/*
 * Copyright © 2010, 2012 Peter Colberg
 *
 * This file is part of HALMD.
 *
 * HALMD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUDA_WRAPPER_DETAIL_ITERATOR_TAG_HPP
#define CUDA_WRAPPER_DETAIL_ITERATOR_TAG_HPP

#include <iterator>

namespace cuda {
namespace detail {

/**
 * Extend STL iterator with a memory tag.
 *
 * This allows to differentiate between device and host memory iterators.
 */

/**
 * Global device memory.
 */
struct device_random_access_iterator_tag : std::random_access_iterator_tag {};

/**
 * Page-locked host memory.
 */
struct host_random_access_iterator_tag : std::random_access_iterator_tag {};

} // namespace detail
} // namespace cuda

#endif /* CUDA_WRAPPER_DETAIL_ITERATOR_TAG_HPP */
