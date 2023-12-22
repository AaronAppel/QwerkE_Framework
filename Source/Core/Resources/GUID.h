#pragma once

static int g_UniqueID = 0; // Put in a .cpp?
static int UniqueID() { return g_UniqueID++; };
