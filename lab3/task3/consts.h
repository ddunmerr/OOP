#pragma once
#include <string>

// NAMES
const std::string APU = "Apu";
const std::string BURNS = "Mr. Burns";
const std::string BART_AND_LISA = "Bart & Lisa";
const std::string HOMER = "Homer";
const std::string MARGE = "Marge";

// APU LOGS
const std::string DEPOSITED_CASH = "deposited cash: ";
const std::string PAID_ELECTRICITY = "paid electricity to Burns: ";
const std::string COULDNT_PAY_ELECTRICITY = "could not pay electricity - insufficient funds";

// BART AND LISA LOGS
const std::string RECEIVED_ALLOWANCE = "received allowance: ";
const std::string SPENT_CASH_AT_APU = "spent cash at Apu's: ";
const std::string NO_CASH_TO_SPEND = "no cash to spend";

// BURNS LOGS
const std::string PAID_SALARY = "paid salary to Homer: ";
const std::string COULDNT_PAY_HOMER = "could not pay Homer - insufficient funds";

// HOMER LOGS
const std::string SENT_MONEY_TO_MARGE = "sent money to Marge: ";
const std::string COULDNT_SEND_MONEY_TO_MARGE = "could not send money - insufficient funds";
const std::string WITHDREW_FOR_ELECTRICITY = "withdrew for electricity bill: ";
const std::string WITHDREW_FOR_KIDS = "withdrew cash for kids: ";

// MARGE LOGS
const std::string BOUGHT_GROCERIES = "bought groceries from Apu: ";
const std::string COULDNT_BUY_GROCERIES = "could not buy groceries - insufficient funds";

// BANK LOGS
const std::string AMOUNT = "amount";

// ECONOMY SIMULATION LOGS
const std::string STEP_BEGIN = "\n=== Step ";
const std::string STEP_END = " ===";
const std::string FINAL_REPORT = "\n=== Final Report ===";
const std::string ACCOUNT = "account=";
const std::string CASH = ", cash=";
const std::string NO_BANK_ACCOUNT = " (no bank account)";
const std::string CASH_IN_CIRCULATION = "\nBank cash in circulation: ";
const std::string TOTAL_ON_ACCOUNTS = "Total on accounts: ";
const std::string TOTAL_CASH_HELD_BY_ACTORS = "Total cash held by actors: ";
const std::string SYSTEM_TOTAL = "System total (bank cash + accounts): ";
const std::string EXPECTED_TOTAL = "Expected total: ";
const std::string SYSTEM_IS_CONSISTENT = "SYSTEM IS CONSISTENT - Bank invariants hold";
const std::string SYSTEM_INCONSISTENT = "SYSTEM INCONSISTENT — Expected ";
const std::string SYSTEM_GOT = " but got ";
const std::string DIFFERENCE = ", difference: ";
const std::string ACTORS_HOLD_IN_CASH = "Actors hold in cash: ";

// MAIN
const std::string ENTER_ITERATIONS = "Enter number of iterations: ";

// ERRORS
const std::string ERROR_CANT_DEPOSIT = "could not deposit - not enough cash in bank";
const std::string ERROR_CANT_BE_NEGATIVE = " cannot be negative";
const std::string ERROR_INITIAL_CASH_CANT_BE_NEGATIVE = "Initial cash cannot be negative";
const std::string ERROR_ACCOUNT_DOESNT_EXIST = "Account does not exist ";
const std::string ERROR_INSUFFICIENT_FUNDS_ON_ACCOUNT = "Insufficient funds on account ";
const std::string ERROR_NOT_ENOUGH_CASH_ON_CIRCULATION = "Not enough cash in circulation";
const std::string ERROR_INVALID_NUMBER_OF_ITERATIONS = "Invalid number of iterations";
