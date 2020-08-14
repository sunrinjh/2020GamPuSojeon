#pragma once

template <typename T, UINT MaxElements>
class ZeroRingBuffer {
private:
	UINT start;
	UINT count;
	T elements[MaxElements];

public:
	ZeroRingBuffer() : start(0), count(0) {}

	void Add(T _element) {
		elements[(start + count) % MaxElements] = _element;

		if (count < MaxElements) {
			count++;
		}
		else {
			start = (start + 1) % MaxElements;
		}
	}

	T GetFirst() const {
		return elements[start];
	}

	T GetLast() const {
		return elements[(start + count - 1) % MaxElements];
	}

	T GetCount() const {
		return count;
	}

	void Reset() {
		start = 0;
		count = 0;
	}
};
