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

1) [x] Implement Persistence System
2) [x] Implement Base Command
3) [x] CheckConvertion
4) [x] CheckNPriceCommand
5) [x] ChceckPriceCommand
6) [x] TrackConvertionCommand
7) [x] UntrackConvertionCommnand
8) [x] ListTrackingConvertions
9) [x] Persist Tracking Convertions making sure of updating id counter when loading the app.
10) [ ] CheckPortfolio
11) [ ] CreatePortfolioCommand
12) [ ] DecreaseInvestedCommand
13) [ ] DecrementPortfollioAssetCommand
14) [ ] DeletePortfolioCommand
15) [ ] IncreaseInvestedCommand
16) [ ] IncrementPortfolioAssetCommand
17) [ ] ListPortfoliosCommand
18) [ ] RemoveAssetCommand
19) [ ] SetInvestedCommand
20) [ ] SetPortfolioAssetCommand
21) [ ] HelpCommand
22) [ ] Unify files for persistence.

## Commands

### Check Price
**Description**: Checks the price of a cryptocurrency
```/price <ticker>```

**example:**

```/price BTC```

### Check Price of N tokens
**Description**: Checks the price of a cryptocurrency
```/pricen <amount> <ticker>```

**example:**

```/pricen 12 BTC```

(Checks the price of N BTC)

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


### Untrack Convertion Command
**Description**: Deletes a tracking convertion.

```/tconvdel <id>```

**example:**

```/tconvdel 1```

(Deletes the tracking convertion 1)

### Get Tracking Convertion List Command
**Description**: Returns all the tracking convertions.

```/tconvlist```

**example:**

```/tconvlist```

(Retuns all the convertions that the user is tracking)

### Check Tracking Convertion
**Description**: Checks the status of a given convertion returning the percentage to be done and the current convertion.

```/tconvcheck <id>```

**example:**

```/tconvcheck 1```

(Checks the convertion with id 1)