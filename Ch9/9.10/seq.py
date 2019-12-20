def is_prime(val):
    for i in range(2, val):
        if i * i > val:
            break
        if val % i == 0:
            return False
    return True

if __name__ == '__main__':
    base = 2
    for i in range(1, 60):
        base *= 2
        left = base - 1
        if is_prime(left):
            print(left * base // 2)
