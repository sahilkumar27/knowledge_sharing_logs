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

// Explanation:

**Explanation:**
In this example, the `Car` class directly creates and uses the `Engine` class.
This means `Car` is tightly connected to `Engine`, making it hard to change the engine type later.
If you want to use a different engine, you must change the `Car` class itself.
This is called **tight coupling** and is not flexible.

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

// Explanation:

**Explanation:**
Here, `Car` depends on the `Engine` interface, not a specific engine type.
You can give `Car` any kind of engine (`ElectricEngine`, `PetrolEngine`, etc.) when you create it.
This is called **loose coupling** and makes your code flexible and easy to extend.


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

// Explanation:

**Explanation:**
This class does too many things: it handles salary, tech stack, and department.
If any of these change, you must update this class, which can cause problems.
According to SRP, each class should do only one job, making code easier to manage and less error-prone.


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

// Explanation:

**Explanation:**
This code uses if-else to check payment type. If you want to add a new payment method,
you must change this class. This violates OCP because you keep modifying old code.

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

// Explanation:

**Explanation:**
Now, each payment method is its own class. To add a new payment type, just create a new class.
The `PaymentProcess` class does not need to change. This follows OCP and makes your code easy to extend.


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
Parent promised → Every Payment supports refund, but CashOnDelivery breaks that promise → LSP Violated

// Explanation:

**Explanation:**
The parent class says all payments can be refunded, but `CashOnDelivery` cannot.
If you use `CashOnDelivery` as a `Payment` and call `refund`, your program crashes.
This breaks LSP because the child class does not behave like the parent.

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

// Explanation:

**Explanation:**
Now, only classes that support refunds implement the `Refundable` interface.
You cannot call `refund` on `CashOnDelivery`, so there are no surprises or crashes.
This follows LSP and makes your code safer.


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
Car is forced to implement fly() even though it doesn't need it ➡️ Interface Segregation Principle violated

// Explanation:

**Explanation:**
The `IVehicle` interface forces all vehicles to have both `drive` and `fly` methods.
Regular cars cannot fly, so they have to add code that throws an error.
This is confusing and can cause bugs. ISP says only add methods that are needed.

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

// Explanation:

**Explanation:**
Now, each class only implements the methods it needs.
Cars only drive, airplanes only fly, and flying cars do both.
This makes your code clear and easy to use.


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
High-level module (DataAccessLayer) depends on low-level module (FileLogger)
➡️ Changing logger type requires modifying business logic → DIP violated

// Explanation:

**Explanation:**
`DataAccessLayer` directly creates and uses `FileLogger`.
If you want to use a different logger (like `DatabaseLogger`), you must change `DataAccessLayer`.
This is not flexible and violates DIP.

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

// Explanation:

**Explanation:**
Now, `DataAccessLayer` uses the `ILogger` interface, not a specific logger.
You can give it any logger you want. This makes your code flexible and easy to change.

**Detailed DIP Explanation:**
The Dependency Inversion Principle (DIP) says that high-level modules (like business logic) should not depend on low-level modules (like utility classes), but both should depend on abstractions (interfaces or abstract classes).

In the good design above:
* The `DataAccessLayer` (high-level class) does not create or depend directly on a specific logger (low-level class).
* Instead, it depends on the `ILogger` interface, which is an abstraction.
* Any class that implements `ILogger` (such as `FileLogger` or `DatabaseLogger`) can be used by `DataAccessLayer`.
* The logger is provided to `DataAccessLayer` through its constructor (this is called dependency injection).

**Why is this good?**
- You can easily switch logging strategies (file, database, cloud, etc.) without changing the business logic in `DataAccessLayer`.
- Your code is more flexible, testable, and maintainable.
- High-level and low-level modules are decoupled, so changes in one do not force changes in the other.

**Summary:**
By depending on abstractions and using dependency injection, the good design fully supports DIP and avoids the problems of tight coupling.


## Memory Trick
 -  SRP         One class → One job
 - OCP         Extend without modifying
 - LSP         Child behaves like parent
 - ISP         Small interfaces
 - DIP         Depend on interface
