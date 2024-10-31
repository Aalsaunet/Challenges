namespace WorkdayNet
{
    public interface IWorkdayCalendar
    {
        void SetHoliday(DateTime date);
        void SetRecurringHoliday(int month, int day);
        void SetWorkdayStartAndStop(int startHours, int startMinutes,
        int stopHours, int stopMinutes);
        DateTime GetWorkdayIncrement(DateTime startDate, decimal
        incrementInWorkdays);
    }

    public class WorkdayCalendar : IWorkdayCalendar
    {
        private TimeSpan workdayStart;
        private TimeSpan workdayEnd;
        private List<DateTime> holidays = new List<DateTime>();
        private List<(int month, int day)> recurringHolidays = new List<(int, int)>();

        public void SetHoliday(DateTime date)
        {
            holidays.Add(date.Date);
        }

        public void SetRecurringHoliday(int month, int day)
        {
            recurringHolidays.Add((month, day));
        }

        public void SetWorkdayStartAndStop(int startHours, int startMinutes, int stopHours, int stopMinutes)
        {
            workdayStart = new TimeSpan(startHours, startMinutes, 0);
            workdayEnd = new TimeSpan(stopHours, stopMinutes, 0);
        }

        private bool IsWorkday(DateTime date)
        {
            if (date.DayOfWeek == DayOfWeek.Saturday || date.DayOfWeek == DayOfWeek.Sunday)
                return false;

            if (holidays.Contains(date.Date))
                return false;

            foreach (var (month, day) in recurringHolidays)
            {
                if (date.Month == month && date.Day == day)
                    return false;
            }
            return true;
        }

        private DateTime GetNextOrPreviousWorkday(DateTime date, int increment)
        {
            while (!IsWorkday(date))
            {
                date = date.AddDays(increment);
            }
            return date;
        }

        private DateTime AdjustToWorkday(DateTime date, bool aheadInTime, int dayIncrement)
        {
            if (aheadInTime && date.TimeOfDay < workdayStart)
            {
                return new DateTime(date.Year, date.Month, date.Day, workdayStart.Hours, workdayStart.Minutes, 0);
            }
            else if (!aheadInTime && date.TimeOfDay < workdayStart)
            {
                date = GetNextOrPreviousWorkday(date, dayIncrement);
                return new DateTime(date.Year, date.Month, date.Day, workdayEnd.Hours, workdayEnd.Minutes, 0);
            }
            else if (aheadInTime && date.TimeOfDay > workdayEnd)
            {
                date = GetNextOrPreviousWorkday(date, dayIncrement);
                return new DateTime(date.Year, date.Month, date.Day, workdayStart.Hours, workdayStart.Minutes, 0);
            }
            else if (!aheadInTime && date.TimeOfDay > workdayEnd)
            {
                return new DateTime(date.Year, date.Month, date.Day, workdayEnd.Hours, workdayEnd.Minutes, 0);
            }
            return date;
        }

        private DateTime AddFractionalWorkday(DateTime date, decimal fractionalDay, bool aheadInTime, int dayIncrement)
        {
            TimeSpan workdayDuration = workdayEnd - workdayStart;
            double fractionalSeconds = workdayDuration.TotalSeconds * (double)Math.Abs(fractionalDay);
            TimeSpan remainingOfDay = aheadInTime ? workdayEnd - date.TimeOfDay : date.TimeOfDay - workdayStart;
            double overflow = fractionalSeconds - remainingOfDay.TotalSeconds;
            DateTime targetDate = date.AddSeconds(dayIncrement * fractionalSeconds);

            if (overflow > 0) {
                targetDate = AdjustToWorkday(targetDate, aheadInTime, dayIncrement);
                targetDate = targetDate.AddSeconds(dayIncrement * overflow);
            }
            
            return targetDate;
        }

        public DateTime GetWorkdayIncrement(DateTime startDate, decimal incrementInWorkdays)
        {
            bool aheadInTime = incrementInWorkdays >= 0 ? true : false;
            int dayIncrement = aheadInTime ? 1 : -1;
            startDate = AdjustToWorkday(startDate, aheadInTime, dayIncrement);

            int wholeDays = (int)incrementInWorkdays;
            decimal fractionalDay = incrementInWorkdays - wholeDays;

            for (int i = 0; i < Math.Abs(wholeDays); i++)
                startDate = GetNextOrPreviousWorkday(startDate.AddDays(dayIncrement), dayIncrement);

            if (fractionalDay != 0)
                startDate = AddFractionalWorkday(startDate, fractionalDay, aheadInTime, dayIncrement);

            return startDate;
        }
    }

    public class Program
    {
        static void Main(string[] args)
        {
            IWorkdayCalendar calendar = new WorkdayCalendar();
            calendar.SetWorkdayStartAndStop(8, 0, 16, 0);
            calendar.SetRecurringHoliday(5, 17);
            calendar.SetHoliday(new DateTime(2004, 5, 27));
            string format = "dd-MM-yyyy HH:mm";
            TestWorkdayIncrement(calendar, new DateTime(2004, 5, 24, 18, 5, 0), -5.5m, "14-05-2004 12:00", format);
            TestWorkdayIncrement(calendar, new DateTime(2004, 5, 24, 19, 3, 0), 44.723656m, "27-07-2004 13:47", format);
            TestWorkdayIncrement(calendar, new DateTime(2004, 5, 24, 18, 3, 0), -6.7470217m, "13-05-2004 10:01", format);
            TestWorkdayIncrement(calendar, new DateTime(2004, 5, 24, 8, 3, 0), 12.782709m, "10-06-2004 14:18", format);
            TestWorkdayIncrement(calendar, new DateTime(2004, 5, 24, 7, 3, 0), 8.276628m, "04-06-2004 10:12", format);
        }

        static void TestWorkdayIncrement(IWorkdayCalendar calendar, DateTime startDate, decimal increment, string expectedDate, string format)
        {
            var incrementedDate = calendar.GetWorkdayIncrement(startDate, increment);
            string result = incrementedDate.ToString(format);
            Console.WriteLine($"{startDate.ToString(format)} med tillegg av {increment} arbeidsdager er {result}");
            Console.WriteLine(result == expectedDate ? "✅ Test bestått" : $"❌ Test feilet (forventet {expectedDate})");
        }
    }
}