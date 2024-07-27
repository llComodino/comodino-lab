    let rec f x n : float =
        if n > 0. then f x n-1. else x *. n;;

    f 2. 4.
