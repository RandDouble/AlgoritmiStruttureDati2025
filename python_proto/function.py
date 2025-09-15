from dataclasses import dataclass


@dataclass
class Elements:
    weight: int
    value: int


def knapsack_solver(
    values: list[Elements], target: int, mode: str = "recursive"
) -> int:
    memory: dict[tuple[int, int], int] = {}
    if mode == "recursive":
        return knapsack_recursive(values, len(values), target, memory)
    elif mode == "stack":
        return knapsack_with_stack(values, len(values), target, memory)
    else:
        raise ValueError(f"Unknown mode {mode}")


def knapsack_recursive(
    values: list[Elements],
    considered: int,
    target: int,
    memory: dict[tuple[int, int], int],
) -> int:
    if target <= 0 or considered <= 0:
        memory[(considered, target)] = 0
        return 0

    el_idx: int = considered - 1

    if (considered, target) not in memory:
        # This should calculate memory[considered - 1, values ]
        knapsack_recursive(values, considered - 1, target, memory)

    if values[el_idx].weight > target:
        memory[(considered, target)] = memory[(considered - 1, target)]
    else:
        memory[(considered, target)] = max(
            memory[(considered - 1, target)],
            values[el_idx].value
            + knapsack_recursive(
                values, considered - 1, target - values[el_idx].weight, memory
            ),
        )
    return memory[(considered, target)]


def knapsack_with_stack(
    values: list[Elements],
    considered: int,
    target: int,
    memory: dict[tuple[int, int], int],
) -> int:
    if considered <= 0 or target <= 0:
        raise ValueError(
            "Number of elements considered and target must be greater than 0"
        )
    stack: list[tuple[int, int]] = [(considered, target)]

    while stack:
        considered_now, target_now = stack[-1]

        if target_now <= 0 or considered_now <= 0:
            memory[(considered_now, target_now)] = 0
            stack.pop()
            continue
        el_idx: int = considered_now - 1

        if (considered_now, target_now) not in memory:
            memory[(considered_now, target_now)] = -1  # Mark as being processed
            # This should calculate memory[considered - 1, values ]
            stack.append((considered_now - 1, target_now))
            # Re-add current state to stack
            # Add dependency to stack, with higher priority
            continue

        if values[el_idx].weight > target_now:
            assert memory[(considered_now - 1, target_now)] != -1, (
                "Dependency not resolved"
            )
            memory[(considered_now, target_now)] = memory[
                (considered_now - 1, target_now)
            ]
        else:
            if (considered_now - 1, target_now - values[el_idx].weight) not in memory:
                stack.append(
                    (considered_now - 1, target_now - values[el_idx].weight)
                )  # Add dependency to stack
                continue

            assert memory[(considered_now - 1, target_now)] != -1, (
                "Dependency not resolved"
            )
            assert (
                memory[(considered_now - 1, target_now - values[el_idx].weight)] != -1
            ), "Dependency not resolved"

            memory[(considered_now, target_now)] = max(
                memory[(considered_now - 1, target_now)],
                values[el_idx].value
                + memory[(considered_now - 1, target_now - values[el_idx].weight)],
            )
        stack.pop()
        # Fine Loop

    return memory[(considered, target)]
