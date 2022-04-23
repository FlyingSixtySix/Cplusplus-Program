// Author Name: Andrew Black

// Date: 2022-03-19

// Course ID: CS-320-T4514

// Description: This is the contact class. It creates and stores contact information.
// See the Constructor for more info.

package main;

import java.util.concurrent.atomic.AtomicLong;

public class Contact {
    private static final AtomicLong idGenerator = new AtomicLong();
    private final String contactID;
    private String firstName;
    private String lastName;
    private String phoneNumber;
    private String address;

    /**
     * The contact information for a person.
     *
     * Contact ID must be 10 characters or fewer and cannot be null or updatable.
     * First name must be 10 characters or fewer and cannot be null.
     * Last name must be 10 characters or fewer and cannot be null.
     * Phone number must be exactly 10 digits and cannot be null.
     * Address must be 30 characters or fewer and cannot be null.
     * @param firstName The first name.
     * @param lastName The last name.
     * @param phoneNumber The phone number.
     * @param address The address.
     */
    public Contact(String firstName, String lastName, String phoneNumber, String address) {
        // Contact ID cannot be changed
        this.contactID = String.valueOf(idGenerator.getAndIncrement());

        this.firstName = validateName(firstName);
        this.lastName = validateName(lastName);
        this.phoneNumber = validatePhoneNumber(phoneNumber);
        this.address = validateAddress(address);
    }

    static String validateName(String name) {
        if (name == null || name.isBlank()) return "NULL";
        if (name.length() > 10) return name.substring(0, 10);
        return name;
    }

    static String validatePhoneNumber(String phoneNumber) {
        if (phoneNumber == null || phoneNumber.isBlank() || phoneNumber.length() != 10) return "5555555555";
        return phoneNumber;
    }

    static String validateAddress(String address) {
        if (address == null || address.isBlank()) return "NULL";
        if (address.length() > 30) return address.substring(0, 30);
        return address;
    }

    public String getContactID() {
        return contactID;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = validateName(firstName);
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = validateName(lastName);
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = validatePhoneNumber(phoneNumber);
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = validateAddress(address);
    }
}