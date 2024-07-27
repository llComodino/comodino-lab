Printf.printf "Welcome to my blackjack game!\n";

(*
 * This function takes a list of cards and returns the total value of the cards
 * in the list.
 *)
let rec total_value (cards : card list) : int =
  match cards with
  | [] -> 0
  | h::t -> h.value + total_value t;

(* 
 * This function takes a list of cards and returns the total value of the cards
 * in the list. It treats aces as 1.
 *)
let rec total_value_ace (cards : card list) : int =
  match cards with
  | [] -> 0
  | h::t -> if h.rank = "A" then 1 + total_value_ace t else h.value + total_value_ace t;

(* 
 * This function takes a list of cards and returns the total value of the cards
 * in the list. It treats aces as 11.
 *)

let rec total_value_ace11 (cards : card list) : int =
  match cards with
  | [] -> 0
  | h::t -> if h.rank = "A" then 11 + total_value_ace11 t else h.value + total_value_ace11 t;

(* 
 * This function takes a list of cards and returns the total value of the cards
 * in the list. It treats aces as 1 if the total value of the cards is over 21.
 *)
let rec total_value_ace1 (cards : card list) : int =
  match cards with
  | [] -> 0
  | h::t -> if h.rank = "A" && total_value_ace t > 10 then 1 + total_value_ace1 t else h.value + total_value_ace1 t;

(* 
 * This function takes a list of cards and returns the total value of the cards
 * in the list. It treats aces as 11 if the total value of the cards is over 21.
 *)

let rec total_value_ace111 (cards : card list) : int =
  match cards with
  | [] -> 0
  | h::t -> if h.rank = "A" && total_value_ace t > 10 then 11 + total_value_ace111 t else h.value + total_value_ace111 t;

(* 
 * This function initialized a deck of cards
 *)
let rec init_deck (cards : card list) : card list =
  match cards with
  | [] -> []
  | h::t -> h::init_deck t;

(* This function shuffles a deck of cards *)
let rec shuffle (cards : card list) : card list =
  match cards with
  | [] -> []
  | h::t -> let rand = Random.int (List.length cards) in
            let rec get_card (cards : card list) (rand : int) : card =
              match cards with
              | [] -> failwith "Error"
              | h::t -> if rand = 0 then h else get_card t (rand - 1)
            in
            let card = get_card cards rand in
            card::shuffle (List.filter (fun x -> x <> card) cards);

(* This function deals a card from the deck to the player *)

let rec deal (cards : card list) (player : card list) : card list * card list =
  match cards with
  | [] -> failwith "Error"
  | h::t -> (t, h::player);

(* This function deals two cards to the player and two cards to the dealer *)
let rec deal2 (cards : card list) (player : card list) (dealer : card list) : card list * card list * card list =
  match cards with
  | [] -> failwith "Error"
  | h::t -> let (cards, player) = deal cards player in
            let (cards, dealer) = deal cards dealer in
            let (cards, player) = deal cards player in
            let (cards, dealer) = deal cards dealer in
            (cards, player, dealer);

(* This function prints the cards in the player's hand *)
let rec print_player (player : card list) : unit =
  match player with
  | [] -> ()
  | h::t -> Printf.printf "%s of %s\n" h.rank h.suit;
            print_player t;

(* This function prints the cards in the dealer's hand *)
let rec print_dealer (dealer : card list) : unit =
  match dealer with
  | [] -> ()
  | h::t -> Printf.printf "%s of %s\n" h.rank h.suit;
            print_dealer t;

(* This function prints the cards in the dealer's hand except for the first card *)
let rec print_dealer2 (dealer : card list) : unit =
  match dealer with
  | [] -> ()
  | h::t -> if h = List.hd dealer then Printf.printf "Hidden\n" else Printf.printf "%s of %s\n" h.rank h.suit;
            print_dealer2 t;

(* This function evaluates who wins the hand *)
let rec evaluate (player : card list) (dealer : card list) : unit =
