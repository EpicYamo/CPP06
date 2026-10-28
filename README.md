# CPP Module 06

C++ casts: converting scalar literals, serializing pointers and identifying dynamic types at runtime.

> Part of the **42 school curriculum**. Built by **Arda Aycan**.

## Exercises

| Exercise | Binary | What it demonstrates |
| --- | --- | --- |
| `ex00` | `convert` | `ScalarConverter::convert` parses a char, int, float or double literal and prints all four representations, including the pseudo-literals; impossible conversions are marked as such. |
| `ex01` | `serializer` | `Serializer` turns a `Data *` into a `uintptr_t` and back with `reinterpret_cast`, proving that the round trip preserves the original pointer. |
| `ex02` | `identify` | `A`, `B` and `C` derive from a polymorphic `Base`; `generate()` returns one at random and `identify()` tells them apart with `dynamic_cast` on both a pointer and a reference. |

## Build and run

Every exercise has its own Makefile and produces its own binary:

```bash
make -C ex00
./ex00/convert 42
```

`make fclean -C <exercise>` removes the binary again.

## Notes

- C++98, `-Wall -Wextra -Werror`.
- `ex00` uses `static_cast` for the numeric conversions, `ex01` uses `reinterpret_cast` for the pointer round trip, and `ex02` uses `dynamic_cast` for runtime type identification.
- `identify(Base &)` in `ex02` relies on the exception thrown by a failed reference cast.

## Author

**Arda Aycan** ([@EpicYamo](https://github.com/EpicYamo)).
