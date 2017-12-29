import numpy as np

def check_one_edit(s, t):
    if np.abs(len(s) - len(t)) > 1:
        return False
    elif len(s) == len(t):
        return check_replace_edit(s, t);
    elif len(s) > len(t):
        return check_insert_edit(s, t)
    else:
        return check_insert_edit(t, s)


def check_insert_edit(s, t):
    """
    s is longer than t.
    """

    # Keep track of number of mistakes
    mistake_count = 0

    # Index trackers for s and t respectively.
    s_i = 0
    t_i = 0

    # Check for insert edits
    while s_i < len(t):
        # If letters are not the same, move the s index and keep t index the same.
        if t[t_i] != s[s_i]:
            mistake_count += 1

            # Check number of mistakes
            if mistake_count > 1:
                return False

            s_i += 1
            continue

        t_i += 1
        s_i += 1

    return True


def check_replace_edit(s, t):
    """
    s is longer than t
    """

    # Mistake counter
    mistake_count = 0
    i = 0

    # Check for more than one mistake
    while i < len(s):
        if s[i] != t[i]:
            mistake_count += 1
            if mistake_count > 1:
                return False
        i += 1

    return True

if __name__ == '__main__':

    print("pale, ple ->", check_one_edit("pale", "ple"))        #True
    print("pales, pale ->", check_one_edit("pales", "pale"))    #True
    print("pale, bale ->", check_one_edit("pale", "bale"))      #True
    print("pale, bake ->", check_one_edit("pale", "bake"))      #False
