# Structs

# Build and run

```sh
just run <struct-name>
```

# Structs available

- `src/heap`: list implemented using a `vec` (see below) that holds the min-heap invariant

  See `print`, `init`, `destroy`, `push`, `pop`, `insert`, `remove`.

- `src/linked_list`: list implemented using single linked nodes

  See `print`, `init`, `destroy`, `push`, `pop`, `insert`, `remove`.
  
  Additional: `insertion_sort`, `merge_sort`.

- `src/vec`: list implemented using a backing self-growing buffer
  
  See `print`, `init`, `destroy`, `push`, `pop`, `insert`, `remove`.
  
  Additional: `insertion_sort`, `merge_sort`.
