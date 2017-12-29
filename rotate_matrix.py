
def rotate_matrix(m):

    finish = len(m) - 1
    for shell in range(int(len(m)/2)):
        start = shell
        for offset in range(finish - start):
            top = m[start][start+offset]
            left = m[finish-offset][start]
            bottom = m[finish][finish-offset]
            right = m[start+offset][finish]

            m[start][start+offset] = left
            m[finish-offset][start] = bottom
            m[finish][finish-offset] = right
            m[start+offset][finish] = top

        finish -= 1

    return m


if __name__ == "__main__":
    m = [[1, 2, 3, 4],
            [5, 6, 7, 8],
            [9, 10, 11, 12],
            [13, 14, 15, 16]]

    m2 = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]]

    for i in range(len(m2)):
        print(m2[i])

    print()
    rotate_matrix(m2)

    for i in range(len(m2)):
        print(m2[i])
