class Friend:

    def __init__(self, name, phone, email, message):
        self._name = name
        self._phone = phone
        self._email = email
        self._message = message

    def name(self):
        return self._name

    def phone(self):
        return self._phone

    def email(self):
        return self._email

    def message(self):
        return self._message

    def info(self):
        print("=======================")
        print("Name: " + self._name)
        print("Phone: " + self._phone)
        print("Email: " + self._email)
        print("=======================")