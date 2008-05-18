/* CUDA memory management functions
 *
 * Copyright (C) 2008  Peter Colberg
 *
 * This program is free software: you can redistribute it and/or modify
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

#ifndef CUDA_MEMORY_HPP
#define CUDA_MEMORY_HPP

#include <cuda/cuda_runtime.h>

namespace cuda
{

// forward declaration
template <typename T>
class vector;

// forward declaration
template <typename T>
class symbol;


namespace host
{

// forward declaration
template <typename T, typename Alloc>
class vector;

// forward declaration
template<typename T>
class allocator;

} // namespace host


/**
 * copy from device memory area to device memory area
 */
template <typename T, typename U>
void copy(vector<T> const& src, vector<U>& dst)
{
    CUDA_CALL(cudaMemcpy(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyDeviceToDevice));
}

/**
 * copy from host memory area to device memory area
 */
template <typename T, typename AllocT, typename U>
void copy(host::vector<T, AllocT> const& src, vector<U>& dst)
{
    CUDA_CALL(cudaMemcpy(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyHostToDevice));
}

/**
 * copy from device memory area to host memory area
 */
template <typename T, typename U, typename AllocU>
void copy(vector<T> const& src, host::vector<U, AllocU>& dst)
{
    CUDA_CALL(cudaMemcpy(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyDeviceToHost));
}

/**
 * copy from host memory area to host memory area
 */
template <typename T, typename AllocT, typename U, typename AllocU>
void copy(host::vector<T, AllocT> const& src, host::vector<U, AllocU>& dst)
{
    CUDA_CALL(cudaMemcpy(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyHostToHost));
}

/**
 * copy from device symbol to host memory area
 */
template <typename T, typename U, typename AllocU>
void copy(symbol<T> const& src, host::vector<U, AllocU>& dst)
{
    CUDA_CALL(cudaMemcpyFromSymbol(dst.data(), reinterpret_cast<const char *>(src.data()), src.size() * sizeof(T), 0, cudaMemcpyDeviceToHost));
}

/*
 * copy from device symbol to device memory area
 */
template <typename T, typename U>
void copy(symbol<T> const& src, vector<U>& dst)
{
    CUDA_CALL(cudaMemcpyFromSymbol(dst.data(), reinterpret_cast<const char *>(src.data()), src.size() * sizeof(T), 0, cudaMemcpyDeviceToDevice));
}

/**
 * copy from host memory area to device symbol
 */
template <typename T, typename AllocT, typename U>
void copy(host::vector<T, AllocT> const& src, symbol<U>& dst)
{
    CUDA_CALL(cudaMemcpyToSymbol(reinterpret_cast<const char *>(dst.data()), src.data(), src.size() * sizeof(T), 0, cudaMemcpyHostToDevice));
}

/**
 * copy from device memory area to device symbol
 */
template <typename T, typename U>
void copy(vector<T> const& src, symbol<U>& dst)
{
    CUDA_CALL(cudaMemcpyToSymbol(reinterpret_cast<const char *>(dst.data()), src.data(), src.size() * sizeof(T), 0, cudaMemcpyDeviceToDevice));
}

#ifdef CUDA_WRAPPER_ASYNC_API

/**
 * asynchronous copy from device memory area to device memory area
 */
template <typename T, typename U>
void copy(vector<T> const& src, vector<U>& dst, stream& stream)
{
    CUDA_CALL(cudaMemcpyAsync(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyDeviceToDevice, stream.data()));
}

/**
 * asynchronous copy from host memory area to device memory area
 */
template <typename T, typename U>
void copy(host::vector<T, host::allocator<T> > const& src, vector<U>& dst, stream& stream)
{
    CUDA_CALL(cudaMemcpyAsync(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyHostToDevice, stream.data()));
}

/**
 * asynchronous copy from host memory area to host memory area
 */
template <typename T, typename U>
void copy(host::vector<T, host::allocator<T> > const& src, host::vector<U, host::allocator<U> >& dst, stream& stream)
{
    CUDA_CALL(cudaMemcpyAsync(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyHostToHost, stream.data()));
}

/**
 * asynchronous copy from device memory area to host memory area
 */
template <typename T, typename U>
void copy(vector<T> const& src, host::vector<U, host::allocator<U> >& dst, stream& stream)
{
    CUDA_CALL(cudaMemcpyAsync(dst.data(), src.data(), src.size() * sizeof(T), cudaMemcpyDeviceToHost, stream.data()));
}

#endif /* CUDA_WRAPPER_ASYNC_API */

} // namespace cuda

#endif /* ! CUDA_MEMORY_HPP */