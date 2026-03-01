# SOLID Principles

**S --- Single Responsibility Principle**\
**O --- Open Closed Principle**\
**L --- Liskov Substitution Principle**\
**I --- Interface Segregation Principle**\
**D --- Dependency Inversion Principle**

------------------------------------------------------------------------

## Overview

SOLID is a set of 5 Object-Oriented Design principles that help in
building maintainable, flexible, scalable and testable systems.

------------------------------------------------------------------------

## Tight Coupling vs Loose Coupling

### Tight Coupling

``` java
class Engine {
    public void start() {
        System.out.println("Engine Started");
    }
}

class Car {
    Engine engine = new Engine();

    public void drive() {
        engine.start();
        System.out.println("Car started");
    }
}
```

### Loose Coupling

``` java
interface Engine {
    void start();
}

class ElectricEngine implements Engine {
    public void start() {
        System.out.println("Electric Engine started");
    }
}

class Car {
    private Engine engine;

    public Car(Engine engine) {
        this.engine = engine;
    }

    public void drive() {
        engine.start();
        System.out.println("Car started");
    }
}
```

------------------------------------------------------------------------

## S --- Single Responsibility Principle

A class should have only one Responsibility.

``` java
class devEmployee { 
    int salary () {
        // Business requirement
    }
    String techStack() {
        // Business requirement

    }
    String department() {
        // Business requirement

    }
}
```

------------------------------------------------------------------------

## O --- Open Closed Principle

Open for extension, closed for modification. 
You should be able to add new feature/behaviour without changing the old code.

``` java
// ❌ Old Design (Violates OCP)

class PaymentProcess {

    void pay(String type) {
        if (type.equals("creditcard")) {
            System.out.println("Paid using Credit Card");
        }
        else if (type.equals("UPI")) {
            System.out.println("Paid using UPI");
        }
    }
}

```

```java
// ✅ Correct Design (Follows OCP)

interface Payment {
    void pay();
}

class CreditCard implements Payment {
    public void pay() {
        System.out.println("Paid using Credit Card");
    }
}

class UPI implements Payment {
    public void pay() {
        System.out.println("Paid using UPI");
    }
}

class NetBanking implements Payment {
    public void pay() {
        System.out.println("Paid using NetBanking");
    }
}

class PaymentProcess {

    private Payment payment;

    public PaymentProcess(Payment payment) {
        this.payment = payment;
    }

    public void processPayment() {
        payment.pay();
    }
}

public class Main {
    public static void main(String[] args) {

        Payment payment = new CreditCard();   // You can switch to UPI / NetBanking
        PaymentProcess process = new PaymentProcess(payment);

        process.processPayment();
    }
}
```

------------------------------------------------------------------------

## L --- Liskov Substitution Principle

A child class must be usable anywhere the parent class is used without breaking the logic or changing expected behaviour.

``` java
// ❌ Old Design (Violates OCP)
// Parent class
class Payment {

    void pay(int amount) {
        System.out.println("Payment done");
    }

    void refund(int amount) {
        System.out.println("Refund processed");
    }
}

// Child class 1 — Works fine
class CreditCardPayment extends Payment {
    // supports both pay and refund → LSP follows
}


// Child class 2 — Problem
class CashOnDelivery extends Payment {

    @Override
    void refund(int amount) {
        throw new RuntimeException("Refund not supported");
    }
}

// Main
public class Main {
    public static void main(String[] args) {

        Payment p = new CashOnDelivery();   // Upcasting
        p.refund(1000);                     // 💥 Runtime crash
    }
}
```
- Problem: 
Parent promised → Every Payment supports refund, but CashOnDelivery breaks that promise → LSP Violated

``` java
// ✅ Correct Design (Follows LSP) - Now we separate behavior into proper abstractions.
interface Payment {
    void pay(int amount);
}

interface Refundable {
    void refund(int amount);
}


class CreditCardPayment implements Payment, Refundable {

    public void pay(int amount) {
        System.out.println("Credit Card Payment done");
    }

    public void refund(int amount) {
        System.out.println("Credit Card Refund processed");
    }
}


class UPI implements Payment, Refundable {

    public void pay(int amount) {
        System.out.println("UPI Payment done");
    }

    public void refund(int amount) {
        System.out.println("UPI Refund processed");
    }
}


class CashOnDelivery implements Payment {

    public void pay(int amount) {
        System.out.println("Cash collected on delivery");
    }
}



public class Main {
    public static void main(String[] args) {

        Payment payment = new CashOnDelivery();
        payment.pay(1000);     // Works perfectly ✅

        Refundable refundable = new CreditCardPayment();
        refundable.refund(500);  // Only refundable payments allow refund ✅
    }
}
```

------------------------------------------------------------------------

## I --- Interface Segregation Principle

This principle states that a class should not be forced to implement interfaces that it does not use.

``` java
// ❌ Wrong Design (Violates ISP)
interface IVehicle {
    void drive();
    void fly();
}

class FlyingCar implements IVehicle {

    public void drive() {
        System.out.println("Flying car driving");
    }

    public void fly() {
        System.out.println("Flying car flying");
    }
}


class Car implements IVehicle {

    public void drive() {
        System.out.println("Car driving");
    }

    public void fly() {
        // Car cannot fly → forced implementation ❌
        throw new UnsupportedOperationException("Car cannot fly");
    }
}
```
- Problem: 
Car is forced to implement fly() even though it doesn't need it ➡️ Interface Segregation Principle violated

```java
// ✅ Correct Design (Follows ISP) - Split large interface into smaller specific interfaces
interface Driveable {
    void drive();
}

interface Flyable {
    void fly();
}


class Car implements Driveable {

    public void drive() {
        System.out.println("Car driving");
    }
}


class FlyingCar implements Driveable, Flyable {

    public void drive() {
        System.out.println("Flying car driving");
    }

    public void fly() {
        System.out.println("Flying car flying");
    }
}



class Airplane implements Flyable {

    public void fly() {
        System.out.println("Airplane flying");
    }
}
```

------------------------------------------------------------------------

## D --- Dependency Inversion Principle

DIP states that a high level class must not depend upon low level class.

``` java
// ❌ Wrong Design (Violates DIP) - High-level class directly depends on low-level class
class FileLogger {

    void log(String message) {
        System.out.println(message);
    }
}


class DataAccessLayer {   // High Level Class

    void addCustomer(String name) {

        // add customer to database

        FileLogger logger = new FileLogger();   // FileLogger (Low Level Class) - Direct dependency ❌ 
        logger.log("Customer added " + name);
    }
}
```
- Problem: 
High-level module (DataAccessLayer) depends on low-level module (FileLogger)
➡️ Changing logger type requires modifying business logic → DIP violated

``` java
// ✅ Correct Design (Follows DIP) - Both depend on abstraction
interface ILogger {
    void log(String message);
}


class FileLogger implements ILogger {

    public void log(String message) {
        System.out.println(message);
    }
}


class DatabaseLogger implements ILogger {

    public void log(String message) {
        System.out.println("Log stored in database: " + message);
    }
}


class DataAccessLayer {

    private ILogger logger;

    // Constructor Dependency Injection
    public DataAccessLayer(ILogger logger) {
        this.logger = logger;
    }

    void addCustomer(String name) {

        // add customer to database

        logger.log("Customer added " + name);
    }
}

// This is for the understanding purpose not related to DIP.
public class Main {        // (High level Class)
    public static void main(String[] args) {

        ILogger logger = new FileLogger();   // Upcastupcasting - Inheritance - Polymorphism
        DataAccessLayer data = new DataAccessLayer(logger);  // DataAccessLayer  (Low Level CLass)

        data.addCustomer("Palash");
    }
}

```

------------------------------------------------------------------------

## Memory Trick
 -  SRP         One class → One job
 - OCP         Extend without modifying
 - LSP         Child behaves like parent
 - ISP         Small interfaces
 - DIP         Depend on interface
