// Author Name: Andrew Black

// Date: 2022-03-19

// Course ID: CS-320-T4514

// Description: This is the contact service. It maintains a list of contacts and has capabilities
// for adding and deleting contacts, as well as updating first name, last name, phone number, and address.

package main;

import java.util.HashMap;
import java.util.Map;

public class ContactService {
    Map<String, Contact> contacts = new HashMap<>();

    /**
     * Adds a new contact.
     * @param firstName The first name.
     * @param lastName The last name.
     * @param number The phone number.
     * @param address The address.
     */
    public void addContact(String firstName, String lastName, String number, String address) {
        Contact contact = new Contact(firstName, lastName, number, address);
        contacts.put(contact.getContactID(), contact);
    }

    /**
     * Gets a contact by its ID.
     * @param contactID The contact ID.
     * @return The contact.
     */
    public Contact getContact(String contactID) {
        return contacts.get(contactID);
    }

    /**
     * Deletes a contact by its ID.
     * @param contactID The contact ID.
     */
    public void deleteContact(String contactID) {
        contacts.remove(contactID);
    }

    /**
     * Updates the first name of a contact by its ID.
     * @param firstName The new first name.
     * @param contactID The contact ID.
     */
    public void updateFirstName(String firstName, String contactID) {
        contacts.get(contactID).setFirstName(firstName);
    }

    /**
     * Updates the last name of a contact by its ID.
     * @param lastName The new last name.
     * @param contactID The contact ID.
     */
    public void updateLastName(String lastName, String contactID) {
        contacts.get(contactID).setLastName(lastName);
    }

    /**
     * Updates the phone number of a contact by its ID.
     * @param phoneNumber The new phone number.
     * @param contactID The contact ID.
     */
    public void updateNumber(String phoneNumber, String contactID) {
        contacts.get(contactID).setPhoneNumber(phoneNumber);
    }

    /**
     * Updates the address of a contact by its ID.
     * @param address The new address.
     * @param contactID The contact ID.
     */
    public void updateAddress(String address, String contactID) {
        contacts.get(contactID).setAddress(address);
    }
}
