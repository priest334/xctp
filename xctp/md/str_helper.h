#pragma once


template <typename _Type>
size_t StrSet(_Type& dest, const char* src) {
	size_t count = 0, size = sizeof(_Type);
	if (!src)
		return count;
	while (count < size && (dest[count++] = *(src++)) != '\0') {
	}
	return count;
}



