package jcpp.management;

import java.io.Serializable;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class ObjectName implements Comparable<ObjectName> , Serializable{

	private static class Property {

		int _key_index;
		int _key_length;
		int _value_length;

		Property(int key_index, int key_length, int value_length) {
			_key_index = key_index;
			_key_length = key_length;
			_value_length = value_length;
		}

		void setKeyIndex(int key_index) {
			_key_index = key_index;
		}
	}


	// TODO: Serialization
	private static final long serialVersionUID = 1081892073854801359L;

	private transient String _canonicalName;

	private transient Property[] _kp_array;

	private transient Property[] _ca_array;

	private transient int _domain_length = 0;

	static final private Property[] _Empty_property_array = new Property[0];

	
	public static ObjectName getInstance(String name) throws Exception {
		return new ObjectName(name);
	}

	public ObjectName(String name) throws Exception, NullPointerException {
		construct(name);
	}

	public static ObjectName getInstance(ObjectName name) throws NullPointerException {
		if (name.getClass().equals(ObjectName.class))
			return name;
		try {
			return new ObjectName(name.getSerializedNameString());
		} catch (Exception e) {
			throw new IllegalArgumentException("Unexpected: " + e);
			// can't happen
		}
	}


	private void construct(String name) throws Exception, NullPointerException {

		// The name cannot be null
		if (name == null)
			throw new NullPointerException("name cannot be null");

		// Test if the name is empty
		if (name.length() == 0) {
			throw new IllegalArgumentException("Argument is empty");
		}

		// initialize parsing of the string
		char[] name_chars = name.toCharArray();
		int len = name_chars.length;
		char[] canonical_chars = new char[len]; // canonical form will be same
												// length at most
		int cname_index = 0;
		int index = 0;
		char c1;

		// parses domain part
		domain_parsing: while (index < len) {
			switch (name_chars[index]) {
			case ':':
				_domain_length = index++;
				break domain_parsing;
			case '=':
				
				int i = ++index;
				while ((i < len) && (name_chars[i++] != ':'))
					if (i == len)
						throw new Exception("Domain part must be specified");
				break;
			case '\n':
				throw new Exception("Invalid character '\\n' in domain name");
			default:
				index++;
				break;
			}
		}

		// check for non-empty properties
		if (index == len)
			throw new Exception("Key properties cannot be empty");

		// we have got the domain part, begins building of _canonicalName
		System.arraycopy(name_chars, 0, canonical_chars, 0, _domain_length);
		canonical_chars[_domain_length] = ':';
		cname_index = _domain_length + 1;

		// parses property list
		Property prop;
		Map<String, Property> keys_map = new HashMap<String, Property>();
		String[] keys;
		String key_name;
		boolean quoted_value;
		int property_index = 0;
		int in_index;
		int key_index, key_length, value_index, value_length;

		keys = new String[10];
		_kp_array = new Property[10];
		
		while (index < len) {
			// standard property case, key part
			in_index = index;
			key_index = in_index;
			if (name_chars[in_index] == '=')
				throw new Exception("Invalid key (empty)");
			while ((in_index < len) && ((c1 = name_chars[in_index++]) != '='))
				switch (c1) {
				case ',':
				case ':':
				case '\n':
					final String ichar = ((c1 == '\n') ? "\\n" : "" + c1);
					throw new Exception("Invalid character '" + ichar + "' in key part of property");
				}
			if (name_chars[in_index - 1] != '=')
				throw new Exception("Unterminated key property part");
			value_index = in_index; // in_index pointing after '=' char
			key_length = value_index - key_index - 1; // found end of key

			
			
			if (in_index < len && name_chars[in_index] == '\"') {
				quoted_value = true;
				// the case of quoted value part
				while ((++in_index < len) && ((c1 = name_chars[in_index]) != '\"')) {
					// the case of an escaped character
					if (c1 == '\\') {
						if (++in_index == len)
							throw new Exception("Unterminated quoted value");
						switch (c1 = name_chars[in_index]) {
						case '\\':
						case '\"':
						case 'n':
							break; // valid character
						default:
							throw new Exception("Invalid escape sequence '\\" + c1 + "' in quoted value");
						}
					} else if (c1 == '\n') {
						throw new Exception("Newline in quoted value");
					} 
				}
				if (in_index == len)
					throw new Exception("Unterminated quoted value");
				else
					value_length = ++in_index - value_index;
			} else {
				quoted_value = false;
				while ((in_index < len) && ((c1 = name_chars[in_index]) != ','))
					switch (c1) {
					case '=':
					case ':':
					case '"':
					case '\n':
						throw new Exception("Invalid character '" + c1 + "' in value part of property");
					default:
						in_index++;
//						break;
					}
				value_length = in_index - value_index;
			}

			// Parsed property, checks the end of name
			if (in_index == len - 1) {
				if (quoted_value)
					throw new Exception("Invalid ending character `" + name_chars[in_index] + "'");
				else
					throw new Exception("Invalid ending comma");
			} else
				in_index++;

			
			prop = new Property(key_index, key_length, value_length);
			
			key_name = name.substring(key_index, key_index + key_length);

			if (property_index == keys.length) {
				String[] tmp_string_array = new String[property_index + 10];
				System.arraycopy(keys, 0, tmp_string_array, 0, property_index);
				keys = tmp_string_array;
			}
			keys[property_index] = key_name;

			addProperty(prop, property_index, keys_map, key_name);
			property_index++;
			index = in_index;
		}

		// computes and set canonical name
		setCanonicalName(name_chars, canonical_chars, keys, keys_map, cname_index, property_index);
	}

	private void addProperty(Property prop, int index, Map<String, Property> keys_map, String key_name) throws Exception {

		if (keys_map.containsKey(key_name))
			throw new Exception("key `" + key_name + "' already defined");

		// if no more space for property arrays, have to increase it
		if (index == _kp_array.length) {
			Property[] tmp_prop_array = new Property[index + 10];
			System.arraycopy(_kp_array, 0, tmp_prop_array, 0, index);
			_kp_array = tmp_prop_array;
		}
		_kp_array[index] = prop;
		keys_map.put(key_name, prop);
	}

	private void setCanonicalName(char[] specified_chars, char[] canonical_chars, String[] keys, Map<String, Property> keys_map, int prop_index, int nb_props) {

		// Sort the list of found properties
		if (_kp_array != _Empty_property_array) {
			String[] tmp_keys = new String[nb_props];
			Property[] tmp_props = new Property[nb_props];

			System.arraycopy(keys, 0, tmp_keys, 0, nb_props);
			Arrays.sort(tmp_keys);
			keys = tmp_keys;
			System.arraycopy(_kp_array, 0, tmp_props, 0, nb_props);
			_kp_array = tmp_props;
			_ca_array = new Property[nb_props];

			// now assigns _ca_array to the sorted list of keys
			// (there cannot be two identical keys in an objectname.
			for (int i = 0; i < nb_props; i++)
				_ca_array[i] = keys_map.get(keys[i]);

			// now we build the canonical name and set begin indexes of
			// properties to reflect canonical form
			int last_index = nb_props - 1;
			int prop_len;
			Property prop;
			for (int i = 0; i <= last_index; i++) {
				prop = _ca_array[i];
				// length of prop including '=' char
				prop_len = prop._key_length + prop._value_length + 1;
				System.arraycopy(specified_chars, prop._key_index, canonical_chars, prop_index, prop_len);
				prop.setKeyIndex(prop_index);
				prop_index += prop_len;
				if (i != last_index) {
					canonical_chars[prop_index] = ',';
					prop_index++;
				}
			}
		}

		
		// we now build the canonicalname string
		_canonicalName = (new String(canonical_chars, 0, prop_index)).intern();
	}

	public String getCanonicalKeyPropertyListString() {
		if (_ca_array.length == 0)
			return "";

		int len = _canonicalName.length();
		
		return _canonicalName.substring(_domain_length + 1, len);
	}

	private String getSerializedNameString() {

		// the size of the string is the canonical one
		final int total_size = _canonicalName.length();
		final char[] dest_chars = new char[total_size];
		final char[] value = _canonicalName.toCharArray();
		final int offset = _domain_length + 1;

		// copy "domain:" into dest_chars
		//
		System.arraycopy(value, 0, dest_chars, 0, offset);

		return new String(dest_chars);
	}

	public String getDomain() {
		return _canonicalName.substring(0, _domain_length);
	}

	@Override
	public int compareTo(ObjectName o) {
		// TODO Auto-generated method stub
		System.out.println("implement me " + this.getClass().getName());
		return 0;
	}
}
