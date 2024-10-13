using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lib3_1
{
    public class AddPlayerWindowFlyoutMenuItem
    {
        public AddPlayerWindowFlyoutMenuItem()
        {
            TargetType = typeof(AddPlayerWindowFlyoutMenuItem);
        }
        public int Id { get; set; }
        public string Title { get; set; }

        public Type TargetType { get; set; }
    }
}