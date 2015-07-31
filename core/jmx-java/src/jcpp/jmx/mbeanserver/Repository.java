package jcpp.jmx.mbeanserver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import jcpp.management.DynamicMBean;
import jcpp.management.ObjectName;

public class Repository {

	// Private fields -------------------------------------------->

	/**
	 * The structure for storing the objects is very basic. A Hashtable is used
	 * for storing the different domains For each domain, a hashtable contains
	 * the instances with canonical key property list string as key and named
	 * object aggregated from given object name and mbean instance as value.
	 */
	private final Map<String, Map<String, NamedObject>> domainTb;

	/**
	 * Number of elements contained in the Repository
	 */
	private volatile int nbElements = 0;

	/**
	 * Domain name of the server the repository is attached to. It is quicker to
	 * store the information in the repository rather than querying the
	 * framework each time the info is required.
	 */
	private final String domain;

	/**
	 * We use a global reentrant read write lock to protect the repository. This
	 * seems safer and more efficient: we are using Maps of Maps, Guaranteing
	 * consistency while using Concurent objects at each level may be more
	 * difficult.
	 **/
	private final ReentrantReadWriteLock lock;

	// Private fields <=============================================

	// Private methods --------------------------------------------->

	private void addNewDomMoi(final DynamicMBean object, final String dom, final ObjectName name) {
		final Map<String, NamedObject> moiTb = new HashMap<String, NamedObject>();
		moiTb.put(name.getCanonicalKeyPropertyListString(), new NamedObject(object));
		domainTb.put(dom, moiTb);
		nbElements++;
	}

	public static boolean wildmatch(char[] str, char[] pat) {
		int stri; // index in str
		int pati; // index in pat
		int starstri; // index for backtrack if "*" attempt fails
		int starpati; // index for backtrack if "*" attempt fails, +1
		final int strlen = str.length;
		final int patlen = pat.length;

		stri = pati = 0;
		starstri = starpati = -1;

		/*
		 * On each pass through this loop, we either advance pati, or we
		 * backtrack pati and advance starstri. Since starstri is only ever
		 * assigned from pati, the loop must terminate.
		 */
		while (true) {
			if (pati < patlen) {
				final char patc = pat[pati];
				switch (patc) {
				default:
					if (stri < strlen && str[stri] == patc) {
						stri++;
						pati++;
						continue;
					}
					break;
				}
			} else if (stri == strlen)
				return true;

			// Mismatched, can we backtrack to a "*"?
			if (starpati < 0 || starstri == strlen)
				return false;

			// Retry the match one position later in str
			pati = starpati;
			starstri++;
			stri = starstri;
		}
	}

	/**
	 * Retrieves the named object contained in repository from the given
	 * objectname.
	 */
	private NamedObject retrieveNamedObject(ObjectName name) {

		// Extract the domain name.
		String dom = name.getDomain().intern();

		// Default domain case
		if (dom.length() == 0) {
			dom = domain;
		}

		Map<String, NamedObject> moiTb = domainTb.get(dom);
		if (moiTb == null) {
			return null; // No domain containing registered object names
		}

		return moiTb.get(name.getCanonicalKeyPropertyListString());
	}

	// Private methods <=============================================

	// Protected methods --------------------------------------------->

	// Protected methods <=============================================

	// Public methods --------------------------------------------->

	/**
	 * Construct a new repository with the given default domain.
	 */
	public Repository(String domain) {
		this(domain, true);
	}

	/**
	 * Construct a new repository with the given default domain.
	 */
	public Repository(String domain, boolean fairLock) {
		lock = new ReentrantReadWriteLock(fairLock);

		domainTb = new HashMap<String, Map<String, NamedObject>>(5);

		if (domain != null && domain.length() != 0)
			this.domain = domain;
		else
			this.domain = "default domain";

		// Creates an new hastable for the default domain
		domainTb.put(this.domain.intern(), new HashMap<String, NamedObject>());
	}

	/**
	 * Returns the list of domains in which any MBean is currently registered.
	 * 
	 */
	public String[] getDomains() {

		lock.readLock().lock();
		final List<String> result;
		try {
			// Temporary list
			result = new ArrayList<String>(domainTb.size());
			for (Map.Entry<String, Map<String, NamedObject>> entry : domainTb.entrySet()) {
				// Skip domains that are in the table but have no
				// MBean registered in them
				// in particular the default domain may be like this
				Map<String, NamedObject> t = entry.getValue();
				if (t != null && t.size() != 0)
					result.add(entry.getKey());
			}
		} finally {
			lock.readLock().unlock();
		}

		// Make an array from result.
		return result.toArray(new String[result.size()]);
	}

	/**
	 * Stores an MBean associated with its object name in the repository.
	 * 
	 * @param object
	 *            MBean to be stored in the repository.
	 * @param name
	 *            MBean object name.
	 */
	public void addMBean(final DynamicMBean object, ObjectName name) throws Exception {

		// Extract the domain name.
		String dom = name.getDomain().intern();
		boolean to_default_domain = false;

		// Set domain to default if domain is empty and not already set
		if (dom.length() == 0) {
			try {
				name = new ObjectName(domain + name.toString());
			} catch (Exception e) {
			}
		}

		// Do we have default domain ?
		if (dom == domain) {
			to_default_domain = true;
			dom = domain;
		} else {
			to_default_domain = false;
		}

		lock.writeLock().lock();
		try {
			// Domain cannot be JMImplementation if entry does not exists
			if (!to_default_domain && dom.equals("JMImplementation") && domainTb.containsKey("JMImplementation")) {
				throw new Exception(new IllegalArgumentException("Repository: domain name cannot be JMImplementation"));
			}

			// If domain not already exists, add it to the hash table
			final Map<String, NamedObject> moiTb = domainTb.get(dom);
			if (moiTb == null) {
				addNewDomMoi(object, dom, name);
				return;
			}

			// Add instance if not already present
			String cstr = name.getCanonicalKeyPropertyListString();
			NamedObject elmt = moiTb.get(cstr);
			if (elmt != null) {
				throw new Exception(name.toString());
			} else {
				nbElements++;
				moiTb.put(cstr, new NamedObject(object));
			}

		} finally {
			lock.writeLock().unlock();
		}
	}

	public boolean contains(ObjectName name) {
		lock.readLock().lock();
		try {
			return (retrieveNamedObject(name) != null);
		} finally {
			lock.readLock().unlock();
		}
	}

	/**
	 * Retrieves the MBean of the name specified from the repository. The object
	 * name must match exactly.
	 * 
	 * @param name
	 *            name of the MBean to retrieve.
	 * 
	 * @return The retrieved MBean if it is contained in the repository, null
	 *         otherwise.
	 */
	public DynamicMBean retrieve(ObjectName name) {

		// Calls internal retrieve method to get the named object
		lock.readLock().lock();
		try {
			NamedObject no = retrieveNamedObject(name);
			if (no == null)
				return null;
			else
				return no.getObject();
		} finally {
			lock.readLock().unlock();
		}
	}

	/**
	 * Selects and retrieves the list of MBeans whose names match the specified
	 * object name pattern and which match the specified query expression
	 * (optionally).
	 * 
	 * @param pattern
	 *            The name of the MBean(s) to retrieve - may be a specific
	 *            object or a name pattern allowing multiple MBeans to be
	 *            selected.
	 * @param query
	 *            query expression to apply when selecting objects - this
	 *            parameter will be ignored when the Repository Service does not
	 *            support filtering.
	 * 
	 * @return The list of MBeans selected. There may be zero, one or many
	 *         MBeans returned in the set.
	 */

	public Integer getCount() {
		return new Integer(nbElements);
	}

	/**
	 * Gets the name of the domain currently used by default in the repository.
	 * 
	 * @return A string giving the name of the default domain name.
	 */
	public String getDefaultDomain() {
		return domain;
	}
}

// Public methods <=============================================
