def zero_matrix(m):

    z_rows = []
    z_cols = []

    for row in range(len(m)):
        for col in range(len(m[0])):
            if m[row][col] == 0:
                if row not in z_rows:
                    z_rows.append(row)
                if col not in z_cols:
                    z_cols.append(col)

    print(z_rows)
    print(z_cols)

    for row in z_rows:
        for i in range(len(m[0])):
                m[row][i] = 0

    for col in z_cols:
        for j in range(len(m)):
            m[j][col] = 0

    return m


if __name__ == "__main__":
    m = [[0, 2, 3, 4],
            [5, 0, 7, 8],
            [9, 10, 11, 12],
            [13, 14, 15, 16]]


    for i in range(len(m)):
        print(m[i])

    print()
    zero_matrix(m)

    for i in range(len(m)):
        print(m[i])
