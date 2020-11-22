# Cryptopricebot

### What it is? 

A telegram bot to check your Crypto investments and keep track of your porfolio.

### Why C++? Python would fit 10000000 times better for that!

I know, it's just because I want to have some practice outside the game engine programming context.

## Platform

Linux (As I want it to run on my ubuntu server I'm just going to make sure that it works on Linux)

## Third Party Keys:

In order to use this project you will need **2 api keys**:

1) **Telegram API KEY** (To be able to send messages to your users)
2) **Nomics** key (To query crypto prices)

Then in order to run the bot you will need to do:

```./crypto_bot <telegram_key> <nomics_key> ```

## Dependencies 

```sudo apt-get install binutils libssl-dev libboost-system-dev zlib1g-dev libcurl4-openssl-dev```

## HOW TO Install telegram library
Go to:
```externals/tgbot-cpp ```

```mkdir build```
```cd build```
```cmake ..```
```cmake --build .```
```sudo make install```

## TODO:

1) [ ] Implement Persistence System
2) [x] Implement Base Command
3) [x] CheckConvertion
4) [ ] CheckNPriceCommand
5) [ ] CheckPortfolio
6) [x] ChceckPriceCommand
7) [ ] CreatePortfolioCommand
8) [ ] DecreaseInvestedCommand
9) [ ] DecrementPortfollioAssetCommand
10) [ ] DeletePortfolioCommand
11) [ ] HelpCommand
12) [ ] IncreaseInvestedCommand
13) [ ] IncrementPortfolioAssetCommand
14) [ ] ListPortfoliosCommand
15) [ ] ListTrackingConvertions
16) [ ] RemoveAssetCommand
17) [ ] RepeatLastCommand
18) [ ] SetInvestedCommand
19) [ ] SetPortfolioAssetCommand
20) [x] TrackConvertionCommand
21) [ ] UntrackConvertionCommnand

## Commands

### Check Price
**Description**: Checks the price of a cryptocurrency
```/price <ticker>```

**example:**

```/price BTC```

### Convertion Command
**Description**: Converts from one cryptocurrency to another
```/conv <amount> <ticker> <target_ticker>```

**example:**

```/conv 10 BTC ETH```

(Checks how many ethereum you could have with 10 Bitcoin)


### Track Convertion Command
**Description**: Periodically checks when an amount of a cryptocurrency will be worth another amount from another and
sends a message to the user when the convertion is valid.

```/tconv <amount> <ticker> <target_amount> <target_ticker>```

**example:**

```/tconv 1 BTC 1000000 USDT```

(Periodically checks when 1 Bitcoin will be worth 1 milion USDT and when the condition will be true it will inform the user about it)