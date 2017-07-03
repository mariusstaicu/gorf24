package gorf24

type CRCLENGTH byte

const (
	CRC_DISABLED = iota
	CRC_8BIT
	CRC_16BIT
)

type DATARATE byte

const (
	RATE_1MBPS DATARATE = iota
	RATE_2MBPS
	RATE_250KBPS
)

type PA_DBM byte

const (
	PA_MIN PA_DBM = iota
	PA_LOW
	PA_HIGH
	PA_MAX
	PA_ERROR // what is this for?
)
