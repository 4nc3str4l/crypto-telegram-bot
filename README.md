# Cryptocurrency Bot for Telegram

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

### Create New Portfolio
**Description**: Creates a new portfolio (don't use spaces for the names)

```/pnew <name>```

**example:**

```/pnew staking_coins```

(Creates a potfolio named "Staking Coins")

### List Portfolios
**Description**: Lists all your portfolios with some metrics about it

```/plist```

**example:**

```/plist```

(A list with all your portfolios should be visible)

### Check Portfolio
**Description**: Returns the information about a given portfolio

```/pcheck <id>```

**example:**

```/pcheck 1```

(Returns the information of the portfolio with id 1)


### Set Invested in Portfolio
**Description**: Sets how much FIAT currency has been invested on the portfolio

```/pset <id> <fiat_quantity>```

**example:**

```/pset 1 1000```

(Sets the the FIAT invested on a the portfolio 1 to 1000€)


### Increase Invested in Portfolio
**Description**: Increases  how much FIAT currency has been invested on the portfolio

```/pinvinc <id> <fiat_quantity>```

**example:**

```/pinvinc 1 1000```

(Increase  the the FIAT invested on a the portfolio 1 to 1000€ if the porfolio had 10000$ now it has 11000$)

### Decrease Invested in Portfolio
**Description**: Decreases how much FIAT currency has been invested on the portfolio

```/pinvdec <id> <fiat_quantity>```

**example:**

```/pinvdec 1 1000```

(Decreases the the FIAT invested on a the portfolio 1 to 1000€ if the porfolio had 10000$ now it has 9000$)

### Set portfolio asset
**Description**: Sets the ammount of an asset for a portfolio

```/pset <id> <quantity> <ticker>```

**example:**

```/pset 1 1000 ADA```

(Sets the amount of ADA for the portfolio with ID 1 to 1000 ADA)

### Increase portfolio asset
**Description**: Increases the ammount of an asset for a portfolio

```/pinc <id> <quantity> <ticker>```

**example:**

```/pinc 1 1000 ADA```

(Increases the amount of ADA for the portfolio with ID 1 for 1000 ADA)

### Decrease portfolio asset
**Description**: Decreases the ammount of an asset for a portfolio

```/pdec <id> <quantity> <ticker>```

**example:**

```/pdec 1 1000 ADA```

(Decreases the amount of ADA for the portfolio with ID 1 to 1000 ADA)

### Remove Asset From Portfolio
**Description**: Removes an asset from a portfolio

```/prem <id> <ticker>```

**example:**

```/prem 1 ADA```

(Removes ADA from portfolio 1)

### Delete Portfolio
**Description**: Deletees a portfolio

```/pdel <id> ```

**example:**

```/pdel 1 ```

(Deletes the portfolio 1)

### Repeat Last Command
**Description**: Repeats the last command

```/repeat ```

or

```/r ```
