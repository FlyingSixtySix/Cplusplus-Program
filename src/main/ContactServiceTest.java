// Author Name: Andrew Black

// Date: 2022-03-19

// Course ID: CS-320-T4514

// Description: This is the unit tests for the contact service (ContactServiceTest)

package main;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@TestMethodOrder(OrderAnnotation.class)
public class ContactServiceTest {
    @Test
    @DisplayName("Test to Update First Name.")
    @Order(1)
    void testUpdateFirstName() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        service.updateFirstName("Sven", "0");
        assertEquals("Sven", service.getContact("0").getFirstName(), "First name was not updated.");
    }

    @Test
    @DisplayName("Test to Update Last Name.")
    @Order(2)
    void testUpdateLastName() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        service.updateLastName("Shirley", "1");
        assertEquals("Shirley", service.getContact("1").getLastName(), "Last name was not updated.");
    }

    @Test
    @DisplayName("Test to update phone number.")
    @Order(3)
    void testUpdatePhoneNumber() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        service.updateNumber("5555550000", "2");
        assertEquals("5555550000", service.getContact("2").getPhoneNumber(), "Phone number was not updated.");
    }

    @Test
    @DisplayName("Test to update address.")
    @Order(4)
    void testUpdateAddress() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        service.updateAddress("555 Nowhere Ave", "3");
        assertEquals("555 Nowhere Ave", service.getContact("3").getAddress(), "Address was not updated.");
    }

    @Test
    @DisplayName("Test to ensure that service correctly deletes contacts.")
    @Order(5)
    void testDeleteContact() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        service.deleteContact("4");
        Map<String, Contact> emptyContacts = new HashMap<>();
        assertEquals(service.contacts, emptyContacts, "The contact was not deleted.");
    }

    @Test
    @DisplayName("Test to ensure that service can add a contact.")
    @Order(6)
    void testAddContact() {
        ContactService service = new ContactService();
        service.addContact("Dr.", "Cross", "5555551111", "123 Lollypop Lane");
        assertNotNull(service.getContact("0"), "Contact was not added correctly.");
    }

}