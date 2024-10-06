
<!-- README.md is generated from README.Rmd. Please edit that file -->

# strzip

<!-- badges: start -->

[![R-CMD-check](https://github.com/schochastics/strzip/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/schochastics/strzip/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

In general compression utilities such as zip, gzip do not compress short
strings well and often expand them. `strzip` wraps two short string
compression C libraries:

- SMAZ: <https://github.com/antirez/smaz> (`str_compress_raw()`)
- Unishox2 <https://github.com/siara-cc/Unishox2> (`str_compress()`)

to compress short strings. In practice, `str_compress()` is safer to use
and also comes with a S3 class `strzip` with its own methods.

## Installation

You can install the development version of strzip from
[GitHub](https://github.com/) with:

``` r
# install.packages("pak")
pak::pak("schochastics/strzip")
```

## Example

``` r
library(strzip)

short_strings <- c(
    "Hello, how are you today? 😊", "The world is beautiful. 🌍", "Life is full of surprises.",
    "Coding is fun and challenging!", "Bonjour, ça va?", "Привет, как дела?", "Ciao, come stai?",
    "今日は素晴らしい日ですね！", "¡Hola! ¿Cómo estás?",
    "I love learning new things every day.", "It's a sunny day outside. ☀️",
    "Emojis make conversations fun! 😄", "Cats are adorable. 🐱", "Would you like some coffee? ☕",
    "The sky is full of stars tonight. ✨", "Lets go for a walk in the park.", "Do you enjoy traveling? ✈️",
    "This pizza is delicious. 🍕", "Let's celebrate this moment! 🎉",
    "Reading a good book is always relaxing.", "Laughter is the best medicine. 😂",
    "Whats your favorite movie?", "I cant wait for the weekend.", "Today is going to be a good day!",
    "I need to finish my project by tomorrow.", "Hes always so helpful and kind.",
    "She loves listening to classical music.", "Don't forget to smile today! 😊", "Do you enjoy working out?",
    "We should hang out more often.", "Lets plan a vacation together.",
    "I just finished watching a great movie.", "Chocolate makes everything better. 🍫",
    "Do you have any plans for tonight?", "I hope you have a great day!",
    "The beach is my favorite place. 🏖️", "Good luck on your exam tomorrow!",
    "Keep calm and carry on. 💪", "Nature always amazes me. 🌲", "The sunset was breathtaking. 🌅",
    "I miss the good old days.", "Hes always full of energy.", "Shes the smartest person I know.",
    "Learning never stops.", "The cake is really tasty. 🎂", "Would you like to join us for dinner?",
    "Its never too late to learn something new.", "Patience is a virtue.", "Family is everything.",
    "Friends make life better.", "I just bought a new book.", "Have you seen this new show?",
    "It's so cold outside today!", "I love the sound of the rain.", "Lets meet at the café later.",
    "You can achieve anything you set your mind to.", "He always knows how to make people laugh.",
    "The mountains are calling, and I must go. 🏔️", "Shes such a talented artist.",
    "This is the best sushi I've ever had! 🍣", "Take care and stay safe.",
    "I hope to see you again soon.", "The journey of a thousand miles begins with a single step.",
    "This is my favorite season of the year.", "Its important to stay hydrated. 💧",
    "I just finished reading a great novel.", "Happiness is contagious.",
    "The universe is full of mysteries.", "Shes always so full of joy. 🌟",
    "What a beautiful garden you have! 🌻", "Hes really passionate about his work.",
    "This app makes life so much easier.", "Im so excited for the concert! 🎵",
    "Shes always so supportive.", "The movie was really thrilling!", "I love trying new recipes.",
    "The museum has a wonderful collection.", "Im feeling really productive today.",
    "Whats your favorite hobby?", "Ive been learning Spanish recently.",
    "The weather is perfect for a picnic.", "Lets go out for dinner tonight.",
    "Her creativity knows no bounds.", "Hes always been a great leader.",
    "Ive never seen anything like this before!", "The world is full of possibilities.",
    "Every day is a new opportunity.", "I feel so grateful for everything.",
    "Music brings people together. 🎶", "Shes a great problem solver.",
    "The stars look so bright tonight. 🌠", "Its time to start a new chapter.",
    "Do you believe in fate?", "Lets explore the city together.",
    "This ice cream is absolutely delicious! 🍦", "He always stays calm under pressure.",
    "I just love sunny mornings.", "Time flies when youre having fun!",
    "Her artwork is truly inspiring.", "The coffee shop has the best cappuccino. ☕"
)

compressed <- str_compress(short_strings)
compressed
#> <compressed string of length 100>

summary(compressed, type = "summary")
#> Minimal compression rate: 0.57 
#> Maximal compression rate: 0.88 
#> Average compression rate: 0.67
```
