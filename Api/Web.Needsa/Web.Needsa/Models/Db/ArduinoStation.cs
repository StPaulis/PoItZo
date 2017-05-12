using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Web.Needsa.Models.Db.Abstract;

namespace Web.Needsa.Models.Db
{
    public class ArduinoStation : EntityDescription
    {
        public string Uri { get; set; }
        public string Location { get; set; }
    }
}