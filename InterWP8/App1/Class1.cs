using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App1
{
    public class Latin9Encoding : LatinEncoding
    {
        public Latin9Encoding()
            : base(CharMap)
        {
        }

        static Latin9Encoding()
        {
            CharMap = new Dictionary<byte, char>();
            CharMap.Add(0xD0, '\u011E');
            CharMap.Add(0xDD, '\u0130');
            CharMap.Add(0xDE, '\u015E');
            CharMap.Add(0xF0, '\u011F');
            CharMap.Add(0xFD, '\u0131');
            CharMap.Add(0xFE, '\u015F');
        }

        public static Dictionary<byte, char> CharMap;

        public override string WebName
        {
            get
            {
                return "iso-8859-9";
            }
        }
    }

    public class Windows1252Encoding : LatinEncoding
    {
        public Windows1252Encoding()
            : base(CharMap)
        {
        }

        static Windows1252Encoding()
        {
            CharMap = new Dictionary<byte, char>();
            CharMap.Add(0x80, '\u20AC');
            CharMap.Add(0x82, '\u201A');
            CharMap.Add(0x83, '\u0192');
            CharMap.Add(0x84, '\u201E');
            CharMap.Add(0x85, '\u2026');
            CharMap.Add(0x86, '\u2020');
            CharMap.Add(0x87, '\u2021');
            CharMap.Add(0x88, '\u02C6');
            CharMap.Add(0x89, '\u2030');
            CharMap.Add(0x8A, '\u0160');
            CharMap.Add(0x8B, '\u2039');
            CharMap.Add(0x8C, '\u0152');
            CharMap.Add(0x8E, '\u017D');
            CharMap.Add(0x91, '\u2018');
            CharMap.Add(0x92, '\u2019');
            CharMap.Add(0x93, '\u201C');
            CharMap.Add(0x94, '\u201D');
            CharMap.Add(0x95, '\u2022');
            CharMap.Add(0x96, '\u2013');
            CharMap.Add(0x97, '\u2014');
            CharMap.Add(0x98, '\u02DC');
            CharMap.Add(0x99, '\u2122');
            CharMap.Add(0x9A, '\u0161');
            CharMap.Add(0x9B, '\u203A');
            CharMap.Add(0x9C, '\u0153');
            CharMap.Add(0x9E, '\u017E');
            CharMap.Add(0x9F, '\u0178');
        }

        public static Dictionary<byte, char> CharMap;

        public override string WebName
        {
            get
            {
                return "Windows-1252";
            }
        }
    }

    public class Latin1Encoding : LatinEncoding
    {
        public Latin1Encoding()
            : base(null)
        {
        }

        public override string WebName
        {
            get
            {
                return "iso-8859-1";
            }
        }
    }

    public abstract class LatinEncoding : Encoding
    {
        protected LatinEncoding(Dictionary<byte, char> map)
        {
            FallbackByte = (byte)'?';
            if (map != null)
            {
                Map = map;
                ReverseMap = new Dictionary<char, byte>(map.Count);
                foreach (var entry in map)
                {
                    ReverseMap[entry.Value] = entry.Key;
                }
            }
        }

        public byte FallbackByte { get; set; }
        public Dictionary<byte, char> Map { get; private set; }
        public Dictionary<char, byte> ReverseMap { get; private set; }

        public override int GetByteCount(char[] chars, int index, int count)
        {
            return count;
        }

        public override int GetBytes(char[] chars, int charIndex, int charCount, byte[] bytes, int byteIndex)
        {
            if (chars == null)
                throw new ArgumentNullException("bytes");

            if (charIndex < 0)
                throw new ArgumentOutOfRangeException("charIndex");

            if (charCount < 0)
                throw new ArgumentOutOfRangeException("charCount");

            if (bytes == null)
                throw new ArgumentNullException("bytes");

            if (byteIndex < 0)
                throw new ArgumentOutOfRangeException("byteIndex");

            if ((charIndex + charCount) > chars.Length)
                throw new ArgumentOutOfRangeException("charCount");

            if ((byteIndex + charCount) > bytes.Length)
                throw new ArgumentOutOfRangeException("charCount");

            for (int i = 0; i < charCount; i++)
            {
                char c = chars[charIndex + i];
                if (ReverseMap != null)
                {
                    byte b;
                    if (ReverseMap.TryGetValue(c, out b))
                    {
                        bytes[byteIndex + i] = b;
                        continue;
                    }
                }
                bytes[byteIndex + i] = c > 255 ? FallbackByte : (byte)c;
            }
            return charCount;
        }

        public override int GetCharCount(byte[] bytes, int index, int count)
        {
            return count;
        }

        public override int GetChars(byte[] bytes, int byteIndex, int byteCount, char[] chars, int charIndex)
        {
            if (bytes == null)
                throw new ArgumentNullException("bytes");

            if (chars == null)
                throw new ArgumentNullException("chars");

            if (byteIndex < 0)
                throw new ArgumentOutOfRangeException("byteIndex");

            if (byteCount < 0)
                throw new ArgumentOutOfRangeException("byteCount");

            if (charIndex < 0)
                throw new ArgumentOutOfRangeException("charIndex");

            if ((byteIndex + byteCount) > bytes.Length)
                throw new ArgumentOutOfRangeException("byteCount");

            if ((charIndex + byteCount) > chars.Length)
                throw new ArgumentOutOfRangeException("byteCount");

            for (int i = 0; i < byteCount; i++)
            {
                if (Map != null)
                {
                    char c;
                    if (Map.TryGetValue(bytes[byteIndex + i], out c))
                    {
                        chars[charIndex + i] = c;
                        continue;
                    }
                }
                chars[charIndex + i] = (char)bytes[byteIndex + i];
            }
            return byteCount;
        }

        public override int GetMaxByteCount(int charCount)
        {
            return charCount;
        }

        public override int GetMaxCharCount(int byteCount)
        {
            return byteCount;
        }
    }


    public class AsciiEncoding : System.Text.Encoding
    {
        public override int GetMaxByteCount(int charCount)
        {
            return charCount;
        }
        public override int GetMaxCharCount(int byteCount)
        {
            return byteCount;
        }
        public override int GetByteCount(char[] chars, int index, int count)
        {
            return count;
        }
        public override byte[] GetBytes(char[] chars)
        {
            return base.GetBytes(chars);
        }
        public override int GetCharCount(byte[] bytes)
        {
            return bytes.Length;
        }
        public override int GetBytes(char[] chars, int charIndex, int charCount, byte[] bytes, int byteIndex)
        {
            for (int i = 0; i < charCount; i++)
            {
                bytes[byteIndex + i] = (byte)chars[charIndex + i];
            }
            return charCount;
        }
        public override int GetCharCount(byte[] bytes, int index, int count)
        {
            return count;
        }
        public override int GetChars(byte[] bytes, int byteIndex, int byteCount, char[] chars, int charIndex)
        {
            for (int i = 0; i < byteCount; i++)
            {
                chars[charIndex + i] = (char)bytes[byteIndex + i];
            }
            return byteCount;
        }
    }


}
