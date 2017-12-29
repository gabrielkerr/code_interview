using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Solution {

    static void Main(String[] args)
    {
        string a = Console.ReadLine();
        string b = Console.ReadLine();

        // Dictionary for first word
        Dictionary<char, int> d = new Dictionary<char, int>();

        // Build the dictionary
        for(int i = 0; i < a.Length; i++)
        {
            if(!d.ContainsKey(a[i]))
            {
                d[a[i]] = 1;
            }
            else
            {
                d[a[i]] += 1;
            }
        }

        // Get deletions.
        int dels = get_deletions(d, b);

        // Write to console.
        Console.WriteLine(dels);
    }

    static int get_deletions(Dictionary<char, int> d, string s)
    {
        // Keep track of deletions.
        int dels = 0;

        // Check if each letter in the string is in the map.
        for(int i = 0; i < s.Length; i++)
        {
            if(!d.ContainsKey(s[i]))
            {
                dels++;
            }
            else
            {
                d[s[i]]--;
            }
        }

        // For add the absolute value of each value to deletions.
        foreach(KeyValuePair<char, int> e in d)
        {
            dels += System.Math.Abs(e.Value);
        }

        return dels;
    }
}

