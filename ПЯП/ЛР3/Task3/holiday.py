class Holiday:
    def __init__(self, holiday_name, invited_name, invited_count):
        self.holiday_name = holiday_name
        self.invited_name = invited_name
        self.invited_count = invited_count

    def family(self):
        try:
            family_count = int(input("Введите количество членов семьи: "))
            if family_count <= self.invited_count:
                return f"{self.invited_name} может пригласить всю семью на праздник {self.holiday_name}."
            else:
                return f"{self.invited_name} не может пригласить всю семью на праздник {self.holiday_name}."
        except ValueError:
            return "Пожалуйста, введите корректное число."
