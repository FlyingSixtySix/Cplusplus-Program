// Author Name: Andrew Black

// Date: 2022-03-19

// Course ID: CS-320-T4514

// Description: This is the unit tests for the contact class (ContactTest).

package main;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.fail;

public class ContactTest {
    @Test
    @DisplayName("Contact ID cannot have more than 10 characters")
    void testContactIDWithMoreThanTenCharacters() {
        Contact contact = new Contact("FirstName", "LastName", "PhoneNumber", "Address");
        if (contact.getContactID().length() > 10) {
            fail("Contact ID has more than 10 characters.");
        }
    }

    @Test
    @DisplayName("Contact First Name cannot have more than 10 characters")
    void testContactFirstNameWithMoreThanTenCharacters() {
        Contact contact = new Contact("11223344556677889900", "LastName", "PhoneNumber", "Address");
        if (contact.getFirstName().length() > 10) {
            fail("First Name has more than 10 characters.");
        }
    }

    @Test
    @DisplayName("Contact Last Name cannot have more than 10 characters")
    void testContactLastNameWithMoreThanTenCharacters() {
        Contact contact = new Contact("FirstName", "11223344556677889900", "PhoneNumber", "Address");
        if (contact.getLastName().length() > 10) {
            fail("Last Name has more than 10 characters.");
        }
    }

    @Test
    @DisplayName("Contact phone number is exactly 10 characters")
    void testContactNumberWithMoreThanTenCharacters() {
        Contact contact = new Contact("FirstName", "LastName", "11223344556677889900", "Address");
        if (contact.getPhoneNumber().length() != 10) {
            fail("Phone number length does not equal 10.");
        }
    }

    @Test
    @DisplayName("Contact address cannot have more than 30 characters")
    void testContactAddressWithMoreThanThirtyCharacters() {
        Contact contact = new Contact("FirstName", "LastName", "PhoneNumber", "1122334455667788990011223344556677889900");
        if (contact.getAddress().length() > 30) {
            fail("Address has more than 30 characters.");
        }
    }

    @Test
    @DisplayName("Contact First Name shall not be null")
    void testContactFirstNameNotNull() {
        Contact contact = new Contact(null, "LastName", "PhoneNumber", "Address");
        assertNotNull(contact.getFirstName(), "First name was null.");
    }

    @Test
    @DisplayName("Contact Last Name shall not be null")
    void testContactLastNameNotNull() {
        Contact contact = new Contact("FirstName", null, "PhoneNumber", "Address");
        assertNotNull(contact.getLastName(), "Last name was null.");
    }

    @Test
    @DisplayName("Contact Phone Number shall not be null")
    void testContactPhoneNotNull() {
        Contact contact = new Contact("FirstName", "LastName", null, "Address");
        assertNotNull(contact.getPhoneNumber(), "Phone number was null.");
    }

    @Test
    @DisplayName("Contact Address shall not be null")
    void testContactAddressNotNull() {
        Contact contact = new Contact("FirstName", "LastName", "PhoneNumber", null);
        assertNotNull(contact.getAddress(), "Address was null.");
    }
}

