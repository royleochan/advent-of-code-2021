def parse_depths(depths):
    return [int(depth) for depth in depths]


def solution1(depths):
    count = 0
    n = len(depths)
    parsed_depths = parse_depths(depths)
    if n == 0:
        return 0

    for i in range(1, n):
        if parsed_depths[i] > parsed_depths[i - 1]:
            count += 1

    return count


def solution2(depths):
    count = 0
    n = len(depths)
    parsed_depths = parse_depths(depths)

    if n < 3:
        return 0

    left, right = 0, 3
    curr_window_sum = parsed_depths[0] + parsed_depths[1] + parsed_depths[2]
    while right < n:
        left += 1
        right += 1
        next_window_sum = 0
        for i in range(left, right):
            next_window_sum += parsed_depths[i]

        count += 1 if next_window_sum > curr_window_sum else 0
        curr_window_sum = next_window_sum

    return count


with open('input.txt') as f:
    lines = f.readlines()
    print(solution2(lines))
