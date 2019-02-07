
// garbage collector on separate thread?
// Thread conflicts:
// creating new instances
// tracking / deleting, possibly no issue? given that 
/*
option 1:
Int i = 5; // new Int with value 5 (call it ~1), ~1 has 1 living reference
Int j = i; // ~1 now has 2 living reference
i = 5; // ~1 back to 1, new Int with value 5 ~2 has 1 living reference
j = i; // ~1 now has 0 living references, so it can be cleaned up by the garbage collector, ~2 has 2 living references
*/
/*
option 1.1: run option 1 on a second thread concurrently
option 1.2: run option 1 on a second thread while doing IO, and then join that thread after the IO is complete
option 1.3: run option 1 on a second thread while doing IO, and stop when the IO is complete (stop as in stop looking, but the current check/action will finish)
option 1.4: run option 1, but instead of holding off until later, destroy an object as soon as its references hits 0
*/
/*
option 2:
Save references:
Int i = 5; references[i] = ~1
Int j = i; references[j] ~1
i = 5; references[i] = ~2
j = i; references[j] = ~2

for every living instance, remove from kill list if it has a living instance,
kill everything left over
*/

// Hardest part of this:
// a.map.select.join.split.map.select
// when when something get stored and released there....?
// a = a.map
// a = a.select
// a = a.join
// a = a.split
// a = a.map
// a = a.select

// the result of a.map exists within the a.map method until it gets assigned
// if you do a = a.map, if ~1 doesnt get decremented until the return of a.map,
// is there ANY possibility that things break
// multiple return types?

// make sure that an instance doesnt appear to the garbage collector until it gets a chance to be referenced

struct Namespace
{
	// Parent
	// Name
	// Child namespaces
	// Variables
	// Classes
	// Methods
}

// Should namespaces be objects as well?

struct Classes
{
	// Compiled Classes
	// meta defined classes
}

struct Class
{
	// Parent class(es)
	// List of living instances
	// Class variables
	// Class methods
	// Instance methods
}
// Classes as objects...?
// Class.class -> itself

struct Object
{
	// Class
	// References
	// Internal (Accessable through C code only)
	// Defined Instance Variables: variables compiled
	// Meta Instance Variables: variables defined through __meta__
}

struct Variable
{
	// Modifiers (public/protected/private,secure)
	// Class => Variable
	// Needed: name (string), value (object)
	// - Implement this in internal? otherwise you end up with infinite Variable:name:Variable:name
	// object.internal = Variable
}