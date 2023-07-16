-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jul 16, 2023 at 03:51 AM
-- Server version: 8.0.32-0ubuntu0.20.04.2
-- PHP Version: 8.2.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `orangtua`
--

-- --------------------------------------------------------

--
-- Table structure for table `911calls`
--

CREATE TABLE `911calls` (
  `ID` int NOT NULL,
  `IssuerName` varchar(24) NOT NULL DEFAULT 'NoName',
  `IssuerID` int NOT NULL DEFAULT '0',
  `Reason` varchar(64) NOT NULL DEFAULT 'NoReason',
  `Type` int NOT NULL DEFAULT '0',
  `Sector` int NOT NULL DEFAULT '0',
  `Number` int NOT NULL DEFAULT '0',
  `Time` int NOT NULL DEFAULT '0',
  `Location` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `acc_preset`
--

CREATE TABLE `acc_preset` (
  `ID` int NOT NULL,
  `OwnerID` int NOT NULL DEFAULT '-1',
  `PresetName` varchar(24) NOT NULL DEFAULT 'Unknown Preset',
  `X` float NOT NULL DEFAULT '0',
  `Y` float NOT NULL DEFAULT '0',
  `Z` float NOT NULL DEFAULT '0',
  `RX` float NOT NULL DEFAULT '0',
  `RY` float NOT NULL DEFAULT '0',
  `RZ` float NOT NULL DEFAULT '0',
  `SX` float NOT NULL DEFAULT '0',
  `SY` float NOT NULL DEFAULT '0',
  `SZ` float NOT NULL DEFAULT '0',
  `Bone` int NOT NULL DEFAULT '0',
  `Model` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `actors`
--

CREATE TABLE `actors` (
  `ID` int NOT NULL,
  `Skin` int NOT NULL DEFAULT '1',
  `Anim` int NOT NULL DEFAULT '0',
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `PosA` float NOT NULL DEFAULT '0',
  `Name` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `World` int NOT NULL DEFAULT '0',
  `Interior` int NOT NULL DEFAULT '0',
  `Business` int NOT NULL DEFAULT '-1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `actors`
--

INSERT INTO `actors` (`ID`, `Skin`, `Anim`, `PosX`, `PosY`, `PosZ`, `PosA`, `Name`, `World`, `Interior`, `Business`) VALUES
(29, 70, 0, -1791.3, -2005.98, 1500.79, 358.943, 'Surgery Doctor', 3, 2, -1),
(30, 71, 0, -1423.84, -285.018, 14.1484, 136.395, 'Airport Security', 0, 0, -1),
(31, 71, 0, -1400.2, -308.691, 14.1484, 132.322, 'Airport Security', 0, 0, -1),
(32, 304, 0, -2580.56, -1383.22, 1500.76, 269.994, 'Driving Instructor', 0, 0, -1),
(33, 291, 1238, -2577.35, -1372.09, 1500.76, 90.6438, 'William Brocks', 0, 0, -1),
(34, 71, 0, -2572.02, -1378.3, 1500.76, 88.8105, 'DMV Security', 0, 0, -1),
(35, 131, 1238, -2072.72, -112.989, 35.186, 86.3366, 'Meryza Kyoko', 0, 0, -1),
(36, 228, 1238, -2072.7, -113.778, 35.186, 91.0368, 'Shuttor Zenky', 0, 0, -1),
(37, 304, 579, -2028.26, -170.905, 34.4595, 68.4767, 'Driving Instructor', 0, 0, -1),
(38, 304, 579, -2056.84, -210.825, 34.4595, 197.716, 'Driving Instructor', 0, 0, -1),
(39, 304, 579, -2085.69, -177.805, 34.4595, 305.817, 'Driving Instructor', 0, 0, -1),
(40, 122, 0, -2096.21, -89.0697, 35.1662, 269.639, 'Sweeper Boss', 0, 0, -1),
(41, 71, 0, -2765.35, 372.193, 6.33979, 269.975, 'Hall Security', 0, 0, -1),
(42, 71, 0, -2765.35, 378.853, 6.33939, 269.035, 'Hall Security', 0, 0, -1),
(43, 71, 0, 2834.41, 2875.96, 320.158, 179.276, 'Hall Security', 1, 1, -1),
(44, 71, 0, 2842.25, 2869.6, 320.158, 269.516, 'Hall Security', 1, 1, -1),
(45, 71, 0, 2860.64, 2876.06, 320.158, 90.288, 'Hall Security', 1, 1, -1),
(46, 11, 0, 1080.19, -960.307, 1338.32, 88.6271, 'Staff', 10, 10, -1),
(47, 227, 1238, 1080.19, -965.32, 1338.32, 92.7004, 'Staff', 10, 10, -1),
(48, 71, 0, 1069.21, -966.947, 1338.32, 358.868, 'Security', 10, 10, -1),
(49, 71, 0, 1033.06, -961.211, 1338.32, 180.893, 'Security', 10, 10, -1),
(50, 67, 1238, -2444.8, -704.82, 133.323, 291.065, 'Armend Syaddu', 0, 0, -1),
(52, 71, 0, -2487.44, -610.879, 132.798, 176.529, 'Security', 0, 0, -1),
(54, 137, 391, -2506.9, -594.978, 132.711, 93.4632, 'Kughar Dixie', 0, 0, -1),
(55, 126, 38, -2525.8, -622.374, 132.751, 180.861, 'Driver Boss', 0, 0, -1),
(56, 260, 1, -2404.57, -595.865, 138.579, 345.507, 'Repair Man', 0, 0, -1),
(57, 261, 0, -2368.93, -692.36, 133.138, 114.578, 'Sausage Man', 0, 0, -1),
(58, 226, 1238, -2413.44, -121.62, 35.3203, 91.1697, 'Angel Sonna', 0, 0, -1),
(59, 71, 0, -2081.39, 1368.03, 7.10156, 268.714, 'Security', 0, 0, -1),
(60, 134, 391, -2077.42, 1400.75, 7.42504, 204.753, 'Pengemis', 0, 0, -1),
(61, 168, 0, 1333.79, 1583.75, 3001.09, 180.02, 'Syaipul Jimal', 0, 7, -1),
(62, 183, 239, 1336.19, 1571.3, 3001.09, 359.566, 'Callo Vimol', 0, 7, -1),
(63, 71, 0, -1258.83, 45.3954, 14.1376, 225.01, 'Security', 0, 0, -1),
(64, 71, 0, -1267.5, 36.7318, 14.1406, 225.636, 'Security', 0, 0, -1),
(65, 16, 0, -1175.78, 15.7618, 14.1484, 44.0694, 'Marshaller', 0, 0, -1),
(66, 16, 0, -1213.85, -21.0189, 14.1484, 44.3827, 'Marshaller', 0, 0, -1),
(67, 171, 0, -1657.83, 1208.4, 7.25, 355.88, 'Dealer Staff', 0, 0, -1),
(68, 71, 0, -2231.13, 305.842, 35.9591, 178.793, 'Bank Security', 0, 0, -1),
(69, 71, 0, -2237.4, 299.58, 35.9591, 266.841, 'Bank Security', 0, 0, -1),
(70, 71, 0, -2231.46, 282.492, 35.959, 267.781, 'Bank Security', 0, 0, -1),
(71, 71, 0, -2234.08, 261.485, 35.959, 357.998, 'Bank Security', 0, 0, -1),
(72, 71, 0, -2217.66, 271.434, 35.959, 1.44483, 'Bank Security', 0, 0, -1),
(73, 71, 0, -2216.24, 304.646, 35.959, 90.119, 'Bank Security', 0, 0, -1),
(74, 148, 0, -2214.36, 278.627, 35.959, 89.324, 'Bank Teller', 0, 0, -1),
(75, 148, 0, -2214.36, 296.885, 35.959, 87.7573, 'Bank Teller', 0, 0, -1),
(76, 147, 0, -2214.36, 287.683, 35.959, 89.324, 'Bank Teller', 0, 0, -1),
(77, 147, 1238, -2208.26, 294.595, 35.959, 16.9434, 'Accountant', 0, 0, -1),
(78, 166, 0, -1772.31, -2011.22, 1500.79, 180.318, 'Receptionist', 3, 2, -1),
(79, 120, 0, -1772.22, -2007.18, 1500.79, 359.448, 'James Harold', 3, 2, -1),
(80, 170, 1238, -1760.77, -2019.51, 1500.79, 359.934, 'Jackson Miller', 3, 2, -1),
(81, 71, 0, -2600.21, 695.447, 28.9531, 177.113, 'Security', 0, 0, -1),
(82, 141, 0, -192.341, 1336.84, 1500.98, 358.102, 'Receptionist', 3, 4, -1),
(84, 83, 1238, -1783.26, -2004.53, 1500.79, 90.4139, 'Reizay Brilliant', 3, 2, -1),
(86, 141, 0, -1760.26, 1097.21, -48.9885, 359.275, 'Receptionist', 0, 10, -1),
(87, 71, 0, -1758.48, 1109.18, -48.9885, 88.4073, 'Flat Security', 0, 10, -1),
(88, 3, 1238, -1769.94, 1099.29, -48.9885, 271.396, 'Wongan Troye', 0, 10, -1),
(89, 98, 1238, -1774.28, 957.112, 24.8828, 0.019782, 'Royye Billed', 0, 0, -1),
(90, 147, 0, 1406.06, -11.2965, 1001, 91.1141, 'Receptionist', 0, 11, -1),
(92, 147, 0, -1950.57, 300.766, 35.4688, 90.0272, 'Dealer Owner', 0, 0, -1),
(93, 306, 0, 101.919, 1062.82, -48.9141, 358.554, 'Police Staff', 3, 3, -1),
(94, 71, 0, 100.21, 1073.23, -48.9141, 269.882, 'Security', 3, 3, -1),
(95, 71, 0, 84.5195, 1066.46, -48.9141, 268.506, 'Security', 3, 3, -1),
(96, 71, 0, 112.011, 1062.74, -48.9141, 357.783, 'Security', 3, 3, -1),
(98, 307, 1238, 62.1941, 1071.52, -50.9141, 180.145, 'Security', 3, 3, -1),
(99, 27, 0, -1924.66, 296.802, 41.0469, 269.269, 'Owner Dealer', 0, 0, -1),
(100, 193, 0, 2.1407, -30.7204, 1003.55, 0.313412, 'Cashier', 1011, 10, 11),
(102, 265, 0, -1572.99, 658.844, 7.1875, 359.71, 'SAPD GUARD', 0, 0, -1),
(106, 71, 0, -780.362, 2745.51, 45.8556, 263.5, 'Joko Makiwi', 0, 0, -1),
(110, 260, 0, -1305.18, 2492.8, 87.1307, 266.812, 'Miner Planit', 0, 0, -1),
(111, 260, 1, -1287.92, 2514.21, 87.068, 32.9413, 'Miner Planit', 0, 0, -1),
(112, 71, 0, -1775.59, -2015.07, 1500.79, 359.401, 'Hospital Security', 3, 2, -1),
(113, 71, 0, -1769.13, -2015.07, 1500.79, 359.714, 'Hospital Security', 3, 2, -1),
(114, 164, 0, -1786.31, -1999.97, 1500.79, 266.509, 'ER Inspector', 3, 2, -1),
(116, 29, 0, -2655.8, 1407.18, 906.273, 273.593, 'Bartender', 0, 3, -1),
(117, 71, 374, -1304.54, 2488.25, 87.1814, 268.252, 'Security', 0, 0, -1),
(118, 71, 374, -1287.26, 2494.68, 87.0727, 112.417, 'Security', 0, 0, -1),
(119, 71, 374, -1322.92, 2546.36, 87.0566, 125.746, 'Security', 0, 0, -1),
(120, 71, 374, -1296.55, 2565.09, 86.0864, 84.7222, 'Security', 0, 0, -1),
(121, 71, 374, -1292.36, 2516.43, 87.1553, 120.106, 'Security', 0, 0, -1),
(122, 71, 374, -1341.65, 2516.67, 87.0419, 292.875, 'Security', 0, 0, -1),
(123, 71, 374, -1344.06, 2539.86, 87.1585, 247.755, 'Security', 0, 0, -1),
(124, 71, 374, -1819.55, -55.6092, 15.1094, 82.3242, 'Security', 0, 0, -1),
(125, 71, 374, -1841.07, -94.4358, 15.117, 356.229, 'Security', 0, 0, -1),
(126, 71, 374, -1817.04, -7.37026, 15.1094, 347.143, 'Security', 0, 0, -1),
(129, 152, 0, -2238.12, 128.587, 1035.41, 357.76, 'Jennie', 1005, 6, 5),
(131, 2, 0, 376.48, -65.8489, 1001.51, 185.773, 'James_Edgard', 1014, 10, 14),
(132, 2, 0, 376.484, -65.8468, 1001.51, 179.916, 'Hoova', 1001, 10, 1),
(133, 140, 1, 207.594, -98.5134, 1005.26, 178.149, 'Kasir', 1007, 15, 7),
(135, 2, 0, 2.12888, -30.7013, 1003.55, 0.424746, 'Joestot ', 1015, 10, 15),
(136, 2, 0, 376.935, -65.8476, 1001.51, 176.737, 'Redmount', 1008, 10, 8),
(137, 2, 0, -2238.13, 128.424, 1035.41, 353.637, 'Kasir', 1031, 6, 31),
(138, 167, 0, 377.277, -65.8443, 1001.51, 179.972, 'Harry', 1020, 10, 20),
(139, 68, 0, 2212.67, -1332.73, 252.411, 274.29, 'Preacher', 0, 1, -1),
(140, 147, 0, -25.9045, -138.388, 1003.55, 179.78, 'Snack Guy', 1035, 16, -1),
(143, 233, 0, -1428.38, -1492.03, 3001.5, 88.5554, 'Mbak Sari', 21, 21, -1),
(144, 240, 0, -1436.1, -1525.17, 3001.51, 269.495, 'Receptionist', 21, 21, -1),
(145, 266, 0, 1386.78, 1565.72, 3001.09, 177.515, 'Security', 19, 19, -1),
(146, 93, 1392, 450.367, -81.8505, 999.555, 180.534, 'Canteen Employee', 19, 4, -1),
(147, 205, 0, 376.399, -65.8491, 1001.51, 173.79, 'Chatime Employee', 1037, 10, -1),
(149, 71, 0, -2465.22, 134.693, 35.1719, 316.695, 'Security', 0, 0, -1);

-- --------------------------------------------------------

--
-- Table structure for table `aksesoris`
--

CREATE TABLE `aksesoris` (
  `ID` int NOT NULL,
  `accID` int DEFAULT NULL,
  `Model` int DEFAULT NULL,
  `Bone` int DEFAULT NULL,
  `Show` int DEFAULT NULL,
  `Type` varchar(32) DEFAULT NULL,
  `Color1` varchar(128) DEFAULT NULL,
  `Color2` varchar(128) DEFAULT NULL,
  `Offset` varchar(24) DEFAULT NULL,
  `Rot` varchar(72) DEFAULT NULL,
  `Scale` varchar(24) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `arrest`
--

CREATE TABLE `arrest` (
  `id` int NOT NULL,
  `owner` int NOT NULL DEFAULT '0',
  `fine` int NOT NULL DEFAULT '0',
  `reason` varchar(64) NOT NULL,
  `date` varchar(40) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `atm`
--

CREATE TABLE `atm` (
  `atmID` int NOT NULL,
  `atmX` float NOT NULL,
  `atmY` float NOT NULL,
  `atmZ` float NOT NULL,
  `atmA` float NOT NULL DEFAULT '0',
  `atmInterior` int NOT NULL,
  `atmWorld` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `atm`
--

INSERT INTO `atm` (`atmID`, `atmX`, `atmY`, `atmZ`, `atmA`, `atmInterior`, `atmWorld`) VALUES
(3, -2226.8, 299.752, 35.959, 227.142, 0, 0),
(5, -2228.38, 298.273, 35.959, 225.338, 0, 0),
(7, -2229.67, 296.786, 35.959, 227.726, 0, 0),
(9, -2231.41, 295.329, 35.959, 224.224, 0, 0),
(10, -2041.63, -123.239, 35.56, 268.034, 0, 0),
(12, -2419.91, 965.652, 45.2969, 89.7685, 0, 0),
(14, 1075.43, -967.177, 1338.32, 178.844, 10, 10),
(18, 2860.68, 2873.32, 320.158, 269.975, 1, 1),
(19, -2692.95, 807.018, 1500.97, 3.9995, 1, 3),
(20, -1767.18, -2008.17, 1500.79, 88.8701, 2, 3),
(23, -2517.58, -624.963, 132.781, 176.546, 0, 0),
(29, -2032.9, 146.15, 28.8359, 88.3609, 0, 0),
(34, -1660.1, 1222.58, 7.25, 45.6989, 0, 0),
(38, -2234.72, -2564.21, 31.9219, 238.391, 0, 0),
(42, 89.5066, 1072.53, -48.9141, 359.583, 3, 3),
(46, -11.9448, -30.9732, 1003.55, 88.4771, 10, 1011),
(52, -1950.44, 296.564, 35.4688, 267.783, 0, 0),
(57, -837.338, 418.781, 997.881, 267.97, 2, 101),
(62, 1420.26, 1317.24, 10.8876, 89.5834, 2, 102),
(64, 1436.82, 1319.98, 10.8806, 272.047, 2, 104),
(72, 204.697, -104.478, 1005.14, 356.737, 15, 1013),
(83, 106.744, 1065.07, -48.9141, 268.779, 3, 3),
(102, -11.9939, -30.945, 1003.55, 91.3878, 10, 1023),
(107, 1436.57, 1320.82, 10.8806, 269.839, 2, 101),
(126, 1379.53, 1538.72, 1510.9, 0.9281, 15, 0),
(134, -11.9407, -30.9071, 1003.55, 79.4189, 10, 1027),
(141, -1914.5, 828.823, 35.3999, 183.188, 0, 0),
(153, -2331.85, -164.781, 35.5547, 91.2074, 0, 0),
(158, -2657.4, 259.956, 4.6328, 177.885, 0, 0),
(165, -1798.42, 1200.6, 25.1194, 359.115, 0, 0),
(176, -1841.04, -96.4547, 15.127, 358.178, 0, 0),
(180, -1751.78, -2007.2, 1500.79, 184.058, 2, 3),
(190, -1445.08, -1529.23, 3001.51, 87.2137, 21, 21),
(191, -253.221, 2598.36, 62.8582, 91.6509, 0, 0),
(193, -2492.09, 2367.98, 10.2812, 91.5413, 0, 0),
(194, -2492.09, 2367.98, 10.2812, 91.5413, 0, 0),
(195, 36.4134, 2151.46, 5.4956, 3.4112, 9, 0),
(219, -1619.16, 680.255, 7.1875, 271.149, 0, 0),
(221, 370.303, 167.085, 1008.38, 178.212, 3, 0),
(246, 1382.53, 1565.65, 3001.09, 358.253, 19, 19),
(248, -1210.8, 1836.42, 41.7188, 137.564, 0, 0),
(249, -204.59, 1334.59, 1500.98, 88.4316, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `banip`
--

CREATE TABLE `banip` (
  `ID` int NOT NULL,
  `IP` varchar(24) NOT NULL DEFAULT '127.0.0.1',
  `Admin` varchar(24) NOT NULL,
  `Reason` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `banneds`
--

CREATE TABLE `banneds` (
  `ID` int NOT NULL,
  `Username` varchar(25) NOT NULL DEFAULT 'None',
  `Admin` varchar(24) NOT NULL DEFAULT 'None',
  `Reason` varchar(128) NOT NULL DEFAULT 'None',
  `Date` varchar(26) NOT NULL DEFAULT 'None',
  `IP` varchar(26) NOT NULL DEFAULT '127.0.0.1'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `business`
--

CREATE TABLE `business` (
  `bizID` int NOT NULL,
  `bizName` varchar(32) NOT NULL DEFAULT 'None Business',
  `bizOwner` int NOT NULL DEFAULT '-1',
  `bizExtX` float NOT NULL DEFAULT '0',
  `bizExtY` float NOT NULL DEFAULT '0',
  `bizExtZ` float NOT NULL DEFAULT '0',
  `bizIntX` float NOT NULL DEFAULT '0',
  `bizIntY` float NOT NULL DEFAULT '0',
  `bizIntZ` float NOT NULL DEFAULT '0',
  `bizProduct1` int NOT NULL DEFAULT '0',
  `bizProduct2` int NOT NULL DEFAULT '0',
  `bizProduct3` int NOT NULL DEFAULT '0',
  `bizProduct4` int NOT NULL DEFAULT '0',
  `bizProduct5` int NOT NULL DEFAULT '0',
  `bizProduct6` int NOT NULL DEFAULT '0',
  `bizProduct7` int NOT NULL DEFAULT '0',
  `bizWorld` int NOT NULL DEFAULT '0',
  `bizInterior` int NOT NULL DEFAULT '0',
  `bizPrice` int NOT NULL DEFAULT '0',
  `bizVault` int NOT NULL DEFAULT '0',
  `bizStock` int NOT NULL DEFAULT '0',
  `bizFuel` int NOT NULL DEFAULT '0',
  `bizType` int NOT NULL DEFAULT '0',
  `bizOwnerName` varchar(64) NOT NULL DEFAULT 'None',
  `bizProdName1` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName2` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName3` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName4` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName5` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName6` varchar(24) NOT NULL DEFAULT 'None',
  `bizProdName7` varchar(24) NOT NULL DEFAULT 'None',
  `bizDeliverX` float NOT NULL DEFAULT '0',
  `bizDeliverY` float NOT NULL DEFAULT '0',
  `bizDeliverZ` float NOT NULL DEFAULT '0',
  `bizCargo` int NOT NULL DEFAULT '1000',
  `bizFuelX` float NOT NULL DEFAULT '0',
  `bizFuelY` float NOT NULL DEFAULT '0',
  `bizFuelZ` float NOT NULL DEFAULT '0',
  `bizDiesel` int NOT NULL DEFAULT '0',
  `bizLocked` int NOT NULL DEFAULT '0',
  `bizDescription1` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription2` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription3` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription4` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription5` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription6` varchar(40) NOT NULL DEFAULT 'No description',
  `bizDescription7` varchar(40) NOT NULL DEFAULT 'No description',
  `bizProduct8` int NOT NULL DEFAULT '0',
  `bizProdName8` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'None',
  `bizDescription8` varchar(42) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'None',
  `bizLastLogin` int NOT NULL DEFAULT '0',
  `bizSealed` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `business_queue`
--

CREATE TABLE `business_queue` (
  `ID` int NOT NULL,
  `Username` varchar(24) NOT NULL,
  `bizID` int UNSIGNED NOT NULL,
  `Message` varchar(32) NOT NULL,
  `Date` int UNSIGNED NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `carstorage`
--

CREATE TABLE `carstorage` (
  `ID` int DEFAULT '0',
  `itemID` int NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int DEFAULT '0',
  `itemQuantity` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `changenamesweb`
--

CREATE TABLE `changenamesweb` (
  `cnID` int NOT NULL,
  `cnOwnerID` int DEFAULT '0',
  `cnOwner` int DEFAULT '0',
  `cnOwnerCharacter` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnReason` varchar(1024) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnOldName` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnOldGender` int DEFAULT '1',
  `cnOldBirthdate` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnOldOrigin` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnName` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnGender` int DEFAULT '1',
  `cnBirthdate` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnOrigin` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  `cnStatus` int DEFAULT '0',
  `cnDate` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `characters`
--

CREATE TABLE `characters` (
  `pID` int NOT NULL,
  `Name` varchar(64) NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `Health` float NOT NULL DEFAULT '100',
  `Interior` int NOT NULL DEFAULT '0',
  `World` int NOT NULL DEFAULT '0',
  `UCP` varchar(22) NOT NULL,
  `Age` int NOT NULL DEFAULT '0',
  `Accent` varchar(32) NOT NULL DEFAULT 'None',
  `Origin` varchar(22) NOT NULL DEFAULT '',
  `Gender` int NOT NULL DEFAULT '0',
  `Skin` int NOT NULL DEFAULT '0',
  `Hunger` float NOT NULL DEFAULT '100',
  `AdminLevel` int NOT NULL DEFAULT '0',
  `Money` int NOT NULL DEFAULT '0',
  `Thirst` float NOT NULL DEFAULT '100',
  `Job` int NOT NULL DEFAULT '0',
  `Gun1` int NOT NULL DEFAULT '0',
  `Gun2` int NOT NULL DEFAULT '0',
  `Gun3` int NOT NULL DEFAULT '0',
  `Gun4` int NOT NULL DEFAULT '0',
  `Gun5` int NOT NULL DEFAULT '0',
  `Gun6` int NOT NULL DEFAULT '0',
  `Gun7` int NOT NULL DEFAULT '0',
  `Gun8` int NOT NULL DEFAULT '0',
  `Gun9` int NOT NULL DEFAULT '0',
  `Gun10` int NOT NULL DEFAULT '0',
  `Gun11` int NOT NULL DEFAULT '0',
  `Gun12` int NOT NULL DEFAULT '0',
  `Gun13` int NOT NULL DEFAULT '0',
  `Ammo1` int NOT NULL DEFAULT '0',
  `Ammo2` int NOT NULL DEFAULT '0',
  `Ammo3` int NOT NULL DEFAULT '0',
  `Ammo4` int NOT NULL DEFAULT '0',
  `Ammo5` int NOT NULL DEFAULT '0',
  `Ammo6` int NOT NULL DEFAULT '0',
  `Ammo7` int NOT NULL DEFAULT '0',
  `Ammo8` int NOT NULL DEFAULT '0',
  `Ammo9` int NOT NULL DEFAULT '0',
  `Ammo10` int NOT NULL DEFAULT '0',
  `Ammo11` int NOT NULL DEFAULT '0',
  `Ammo12` int NOT NULL DEFAULT '0',
  `Ammo13` int NOT NULL DEFAULT '0',
  `Durability1` int NOT NULL DEFAULT '0',
  `Durability2` int NOT NULL DEFAULT '0',
  `Durability3` int NOT NULL DEFAULT '0',
  `Durability4` int NOT NULL DEFAULT '0',
  `Durability5` int NOT NULL DEFAULT '0',
  `Durability6` int NOT NULL DEFAULT '0',
  `Durability7` int NOT NULL DEFAULT '0',
  `Durability8` int NOT NULL DEFAULT '0',
  `Durability9` int NOT NULL DEFAULT '0',
  `Durability10` int NOT NULL DEFAULT '0',
  `Durability11` int NOT NULL DEFAULT '0',
  `Durability12` int NOT NULL DEFAULT '0',
  `Durability13` int NOT NULL DEFAULT '0',
  `HighVelocity1` int NOT NULL DEFAULT '0',
  `HighVelocity2` int NOT NULL DEFAULT '0',
  `HighVelocity3` int NOT NULL DEFAULT '0',
  `HighVelocity4` int NOT NULL DEFAULT '0',
  `HighVelocity5` int NOT NULL DEFAULT '0',
  `HighVelocity6` int NOT NULL DEFAULT '0',
  `HighVelocity7` int NOT NULL DEFAULT '0',
  `HighVelocity8` int NOT NULL DEFAULT '0',
  `HighVelocity9` int NOT NULL DEFAULT '0',
  `HighVelocity10` int NOT NULL DEFAULT '0',
  `HighVelocity11` int NOT NULL DEFAULT '0',
  `HighVelocity12` int NOT NULL DEFAULT '0',
  `HighVelocity13` int NOT NULL DEFAULT '0',
  `Number` int NOT NULL DEFAULT '0',
  `Family` int NOT NULL DEFAULT '-1',
  `FamilyRank` int NOT NULL DEFAULT '0',
  `Faction` int NOT NULL DEFAULT '-1',
  `FactionID` int NOT NULL DEFAULT '-1',
  `FactionRank` int NOT NULL DEFAULT '-1',
  `FactionSkin` int NOT NULL DEFAULT '0',
  `Onduty` int NOT NULL DEFAULT '0',
  `Birthdate` varchar(32) NOT NULL DEFAULT '',
  `Armor` float NOT NULL DEFAULT '0',
  `Salary` int NOT NULL DEFAULT '0',
  `Bank` int NOT NULL DEFAULT '0',
  `InBiz` int NOT NULL DEFAULT '0',
  `InDoor` int NOT NULL DEFAULT '-1',
  `Arrest` int NOT NULL DEFAULT '0',
  `JailTime` int NOT NULL DEFAULT '0',
  `JailReason` varchar(128) NOT NULL DEFAULT 'Unknown reason',
  `JailBy` varchar(24) NOT NULL DEFAULT 'Administrator',
  `Injured` int NOT NULL DEFAULT '0',
  `BusDelay` int NOT NULL DEFAULT '0',
  `SweeperDelay` int NOT NULL DEFAULT '0',
  `TrashmasterDelay` int NOT NULL DEFAULT '0',
  `Credit` int NOT NULL DEFAULT '0',
  `Healthy` float NOT NULL DEFAULT '100',
  `Head` float NOT NULL DEFAULT '100',
  `RightArm` float NOT NULL DEFAULT '100',
  `LeftArm` float NOT NULL DEFAULT '100',
  `Torso` float NOT NULL DEFAULT '100',
  `RightLeg` float NOT NULL DEFAULT '100',
  `LeftLeg` float NOT NULL DEFAULT '100',
  `Groin` float NOT NULL DEFAULT '100',
  `MaskID` int NOT NULL DEFAULT '0',
  `Exp` int NOT NULL DEFAULT '0',
  `Level` int NOT NULL DEFAULT '1',
  `Registered` int NOT NULL DEFAULT '0',
  `LastLogin` int NOT NULL DEFAULT '0',
  `Minute` int NOT NULL DEFAULT '0',
  `Second` int NOT NULL DEFAULT '0',
  `Hour` int NOT NULL DEFAULT '0',
  `Paycheck` int NOT NULL DEFAULT '0',
  `InHouse` int NOT NULL DEFAULT '-1',
  `Quitjob` int NOT NULL DEFAULT '0',
  `Channel` int NOT NULL DEFAULT '0',
  `Funds` int NOT NULL DEFAULT '0',
  `Bullet1` int NOT NULL DEFAULT '0',
  `Bullet2` int NOT NULL DEFAULT '0',
  `Bullet3` int NOT NULL DEFAULT '0',
  `Bullet4` int NOT NULL DEFAULT '0',
  `Bullet5` int NOT NULL DEFAULT '0',
  `Bullet6` int NOT NULL DEFAULT '0',
  `Bullet7` int NOT NULL DEFAULT '0',
  `IDCard` int NOT NULL DEFAULT '0',
  `IDCardExpired` int NOT NULL DEFAULT '0',
  `DrivingLicense` int NOT NULL DEFAULT '0',
  `FishDelay` int NOT NULL DEFAULT '0',
  `Fish1` float NOT NULL DEFAULT '0',
  `Fish2` float NOT NULL DEFAULT '0',
  `Fish3` float NOT NULL DEFAULT '0',
  `Fish4` float NOT NULL DEFAULT '0',
  `Fish5` float NOT NULL DEFAULT '0',
  `Fish6` float NOT NULL DEFAULT '0',
  `Fish7` float NOT NULL DEFAULT '0',
  `Fish8` float NOT NULL DEFAULT '0',
  `Fish9` float NOT NULL DEFAULT '0',
  `Fish10` float NOT NULL DEFAULT '0',
  `FishName1` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName2` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName3` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName4` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName5` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName6` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName7` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName8` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName9` varchar(24) NOT NULL DEFAULT 'Empty',
  `FishName10` varchar(24) NOT NULL DEFAULT 'Empty',
  `InFlat` int NOT NULL DEFAULT '-1',
  `Coin` int NOT NULL DEFAULT '0',
  `MowerDelay` int NOT NULL DEFAULT '0',
  `DriverDelay` int NOT NULL DEFAULT '0',
  `LumberDelay` int NOT NULL DEFAULT '0',
  `AutoPaycheck` int NOT NULL DEFAULT '0',
  `Job2` int NOT NULL DEFAULT '0',
  `Fever` int NOT NULL DEFAULT '0',
  `Cough` int NOT NULL DEFAULT '0',
  `InWorkshop` int NOT NULL DEFAULT '-1',
  `TogLogin` int NOT NULL DEFAULT '0',
  `Badge` int NOT NULL DEFAULT '0',
  `LumberLicense` int NOT NULL DEFAULT '0',
  `MineDelay` int NOT NULL DEFAULT '0',
  `FactionHour` int NOT NULL DEFAULT '0',
  `FactionMinute` int NOT NULL DEFAULT '0',
  `FactionSecond` int NOT NULL DEFAULT '0',
  `HaulingDelay` int NOT NULL DEFAULT '0',
  `HaulingLicense` int NOT NULL DEFAULT '0',
  `MarryWith` varchar(24) NOT NULL DEFAULT 'Unknown',
  `MarryDate` varchar(28) NOT NULL DEFAULT 'not yet',
  `Masked` int NOT NULL DEFAULT '0',
  `LastIP` varchar(26) NOT NULL DEFAULT '127.0.0.1',
  `CourierDelay` int NOT NULL DEFAULT '0',
  `HudType` int NOT NULL DEFAULT '1',
  `AdminPoint` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `characters`
--

INSERT INTO `characters` (`pID`, `Name`, `PosX`, `PosY`, `PosZ`, `Health`, `Interior`, `World`, `UCP`, `Age`, `Accent`, `Origin`, `Gender`, `Skin`, `Hunger`, `AdminLevel`, `Money`, `Thirst`, `Job`, `Gun1`, `Gun2`, `Gun3`, `Gun4`, `Gun5`, `Gun6`, `Gun7`, `Gun8`, `Gun9`, `Gun10`, `Gun11`, `Gun12`, `Gun13`, `Ammo1`, `Ammo2`, `Ammo3`, `Ammo4`, `Ammo5`, `Ammo6`, `Ammo7`, `Ammo8`, `Ammo9`, `Ammo10`, `Ammo11`, `Ammo12`, `Ammo13`, `Durability1`, `Durability2`, `Durability3`, `Durability4`, `Durability5`, `Durability6`, `Durability7`, `Durability8`, `Durability9`, `Durability10`, `Durability11`, `Durability12`, `Durability13`, `HighVelocity1`, `HighVelocity2`, `HighVelocity3`, `HighVelocity4`, `HighVelocity5`, `HighVelocity6`, `HighVelocity7`, `HighVelocity8`, `HighVelocity9`, `HighVelocity10`, `HighVelocity11`, `HighVelocity12`, `HighVelocity13`, `Number`, `Family`, `FamilyRank`, `Faction`, `FactionID`, `FactionRank`, `FactionSkin`, `Onduty`, `Birthdate`, `Armor`, `Salary`, `Bank`, `InBiz`, `InDoor`, `Arrest`, `JailTime`, `JailReason`, `JailBy`, `Injured`, `BusDelay`, `SweeperDelay`, `TrashmasterDelay`, `Credit`, `Healthy`, `Head`, `RightArm`, `LeftArm`, `Torso`, `RightLeg`, `LeftLeg`, `Groin`, `MaskID`, `Exp`, `Level`, `Registered`, `LastLogin`, `Minute`, `Second`, `Hour`, `Paycheck`, `InHouse`, `Quitjob`, `Channel`, `Funds`, `Bullet1`, `Bullet2`, `Bullet3`, `Bullet4`, `Bullet5`, `Bullet6`, `Bullet7`, `IDCard`, `IDCardExpired`, `DrivingLicense`, `FishDelay`, `Fish1`, `Fish2`, `Fish3`, `Fish4`, `Fish5`, `Fish6`, `Fish7`, `Fish8`, `Fish9`, `Fish10`, `FishName1`, `FishName2`, `FishName3`, `FishName4`, `FishName5`, `FishName6`, `FishName7`, `FishName8`, `FishName9`, `FishName10`, `InFlat`, `Coin`, `MowerDelay`, `DriverDelay`, `LumberDelay`, `AutoPaycheck`, `Job2`, `Fever`, `Cough`, `InWorkshop`, `TogLogin`, `Badge`, `LumberLicense`, `MineDelay`, `FactionHour`, `FactionMinute`, `FactionSecond`, `HaulingDelay`, `HaulingLicense`, `MarryWith`, `MarryDate`, `Masked`, `LastIP`, `CourierDelay`, `HudType`, `AdminPoint`) VALUES
(1, 'Dije_Yusuf', 2698.95, 1773.35, 6.8574, 98, 0, 0, 'vyn', 0, 'None', 'Detroit', 1, 23, 93.9859, 7, 10000, 95.188, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 2, 14, 280, 0, '', 0, 0, 15000, -1, -1, 0, 0, '', '', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 1, 2, 1688905373, 1689443823, 6, 30, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 15, 40, 0, 0, 'Unknown', 'None', 0, '180.252.93.186', 0, 3, 0),
(2, 'Andrean_Lemingston', -2438.82, -642.041, 133.078, 100, 0, 0, 'Luckystar', 0, 'None', 'American', 1, 21, 83.0158, 7, 10000, 86.4189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 3, 15, 276, 0, '28/02/1999', 0, 4000, 15000, -1, -1, 0, 0, '', '', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 1, 1688907951, 1689343069, 49, 56, 0, 0, -1, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 6, 14, 0, 0, 'Unknown', 'None', 0, '158.140.175.162', 0, 2, 1),
(3, 'Hazel_Pierce', -2037.23, -94.1919, 35.1641, 100, 0, 0, 'KNTLMNS', 0, 'None', 'American', 1, 127, 89.6351, 5, 10000, 91.7067, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, 0, 0, 0, '17/08/1995', 0, 0, 15000, -1, -1, 0, 0, '', '', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 1, 1689344494, 1689442517, 26, 57, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 6, 14, 0, 0, 'Unknown', 'None', 0, '36.79.74.219', 0, 1, 1),
(4, 'Purz_Walker', -1625.03, -466.555, 22.0878, 100, 0, 0, 'Puur', 0, 'None', 'USA', 1, 2, 99.83, 7, 10000, 99.8639, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, 0, 0, 0, '28/11/1999', 0, 0, 15000, -1, -1, 0, 0, '', '', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 1, 1689426627, 1689426695, 1, 5, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 6, 14, 0, 0, 'Unknown', 'None', 0, '127.0.0.1', 0, 1, 1),
(5, 'Jesson_Susanto', 0, 0, 0, 100, 0, 0, 'budi123', 0, 'None', 'USA', 1, 0, 100, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, '01/01/1999', 0, 0, 0, 0, -1, 0, 0, 'Unknown reason', 'Administrator', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 0, 1689443683, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Unknown', 'not yet', 0, '127.0.0.1', 0, 1, 0),
(6, 'Elon_Mus', 0, 0, 0, 100, 0, 0, 'budi123', 0, 'None', 'USA', 1, 0, 100, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, '01/01/1999', 0, 0, 0, 0, -1, 0, 0, 'Unknown reason', 'Administrator', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 0, 1689443722, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Unknown', 'not yet', 0, '127.0.0.1', 0, 1, 0),
(11, 'Mark_Susanto', -1482.42, -271.129, 14, 95, 0, 0, 'budi123', 0, 'None', 'USA', 1, 2, 97.3208, 0, 10000, 97.8613, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, '01/01/1999', 0, 0, 15000, 0, -1, 0, 0, 'Unknown reason', 'Administrator', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 1, 1689445173, 1689445523, 4, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Unknown', 'not yet', 0, '36.73.32.82', 0, 1, 0),
(12, 'Marcelio_Hawkins', -1893.41, -569.085, 24.6176, 100, 0, 0, 'Anura', 0, 'None', 'USA', 1, 2, 99.5371, 7, 10000, 99.6299, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, 0, 0, '02/02/1980', 0, 0, 15000, 0, -1, 0, 0, 'Unknown reason', 'Administrator', 0, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 1, 1689445176, 1689445978, 4, 36, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', 'Empty', -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Unknown', 'not yet', 0, '103.111.102.58', 0, 1, 0);

-- --------------------------------------------------------

--
-- Table structure for table `contacts`
--

CREATE TABLE `contacts` (
  `ID` int DEFAULT '0',
  `contactID` int NOT NULL,
  `contactName` varchar(32) DEFAULT NULL,
  `contactNumber` int DEFAULT '0',
  `contactOwner` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `crates`
--

CREATE TABLE `crates` (
  `ID` int NOT NULL,
  `Type` int NOT NULL DEFAULT '0',
  `Vehicle` int NOT NULL DEFAULT '-1'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `crime_record`
--

CREATE TABLE `crime_record` (
  `ID` int NOT NULL,
  `PlayerID` int NOT NULL DEFAULT '-1',
  `Issuer` varchar(24) NOT NULL DEFAULT 'Police Officer',
  `Date` varchar(18) NOT NULL DEFAULT '01/01/2022',
  `Status` int NOT NULL DEFAULT '1',
  `Description` varchar(64) NOT NULL DEFAULT 'Unknown Charge'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `damagelog`
--

CREATE TABLE `damagelog` (
  `ID` int NOT NULL,
  `PlayerID` int NOT NULL DEFAULT '-1',
  `Amount` int NOT NULL DEFAULT '0',
  `Bodypart` int NOT NULL DEFAULT '0',
  `Time` int NOT NULL DEFAULT '0',
  `Weaponid` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `dealer`
--

CREATE TABLE `dealer` (
  `ID` int NOT NULL,
  `Owner` int NOT NULL DEFAULT '-1',
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `SpawnX` float NOT NULL DEFAULT '0',
  `SpawnY` float NOT NULL DEFAULT '0',
  `SpawnZ` float NOT NULL DEFAULT '0',
  `SpawnA` float NOT NULL DEFAULT '0',
  `Name` varchar(24) NOT NULL DEFAULT 'Undefined',
  `Stock` int NOT NULL DEFAULT '0',
  `Vehicle1` int NOT NULL DEFAULT '0',
  `Vehicle2` int NOT NULL DEFAULT '0',
  `Vehicle3` int NOT NULL DEFAULT '0',
  `Vehicle4` int NOT NULL DEFAULT '0',
  `Vehicle5` int NOT NULL DEFAULT '0',
  `Vehicle6` int NOT NULL DEFAULT '0',
  `Price` int NOT NULL DEFAULT '0',
  `Cost1` int NOT NULL DEFAULT '0',
  `Cost2` int NOT NULL DEFAULT '0',
  `Cost3` int NOT NULL DEFAULT '0',
  `Cost4` int NOT NULL DEFAULT '0',
  `Cost5` int NOT NULL DEFAULT '0',
  `Cost6` int NOT NULL DEFAULT '0',
  `Stock1` int NOT NULL DEFAULT '0',
  `Stock2` int NOT NULL DEFAULT '0',
  `Stock3` int NOT NULL DEFAULT '0',
  `Stock4` int NOT NULL DEFAULT '0',
  `Stock5` int NOT NULL DEFAULT '0',
  `Stock6` int NOT NULL DEFAULT '0',
  `Vault` int NOT NULL DEFAULT '0',
  `VIP` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dealer`
--

INSERT INTO `dealer` (`ID`, `Owner`, `PosX`, `PosY`, `PosZ`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnA`, `Name`, `Stock`, `Vehicle1`, `Vehicle2`, `Vehicle3`, `Vehicle4`, `Vehicle5`, `Vehicle6`, `Price`, `Cost1`, `Cost2`, `Cost3`, `Cost4`, `Cost5`, `Cost6`, `Stock1`, `Stock2`, `Stock3`, `Stock4`, `Stock5`, `Stock6`, `Vault`, `VIP`) VALUES
(3, -1, -1991.88, 167.266, 27.5391, 0, 0, 0, 0, 'Undefined', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `dealervehicle`
--

CREATE TABLE `dealervehicle` (
  `ID` int NOT NULL,
  `DealerID` int NOT NULL DEFAULT '-1',
  `Model` int NOT NULL DEFAULT '0',
  `Stock` int NOT NULL DEFAULT '0',
  `Price` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dealervehicle`
--

INSERT INTO `dealervehicle` (`ID`, `DealerID`, `Model`, `Stock`, `Price`) VALUES
(2, 1, 562, 50, 150000),
(3, 1, 521, 10, 25000),
(4, 2, 560, 10, 15000);

-- --------------------------------------------------------

--
-- Table structure for table `donation_characters`
--

CREATE TABLE `donation_characters` (
  `ID` int NOT NULL,
  `Level` int NOT NULL DEFAULT '0',
  `Expired` int NOT NULL DEFAULT '0',
  `pID` int NOT NULL DEFAULT '-1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `donation_characters`
--

INSERT INTO `donation_characters` (`ID`, `Level`, `Expired`, `pID`) VALUES
(1, 3, 1690535834, 55);

-- --------------------------------------------------------

--
-- Table structure for table `donation_code`
--

CREATE TABLE `donation_code` (
  `ID` int NOT NULL,
  `Code` varchar(24) NOT NULL,
  `Level` int NOT NULL DEFAULT '0',
  `Duration` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `doors`
--

CREATE TABLE `doors` (
  `ID` int NOT NULL,
  `name` varchar(50) DEFAULT 'None',
  `password` varchar(50) DEFAULT '',
  `icon` int DEFAULT '19130',
  `mapicon` tinyint NOT NULL DEFAULT '0',
  `locked` int NOT NULL DEFAULT '0',
  `admin` int NOT NULL DEFAULT '0',
  `vip` int NOT NULL DEFAULT '0',
  `faction` int NOT NULL DEFAULT '0',
  `family` int NOT NULL DEFAULT '-1',
  `garage` tinyint NOT NULL DEFAULT '0',
  `custom` int NOT NULL DEFAULT '0',
  `extvw` int DEFAULT '0',
  `extint` int DEFAULT '0',
  `extposx` float DEFAULT '0',
  `extposy` float DEFAULT '0',
  `extposz` float DEFAULT '0',
  `extposa` float DEFAULT '0',
  `intvw` int DEFAULT '0',
  `intint` int NOT NULL DEFAULT '0',
  `intposx` float DEFAULT '0',
  `intposy` float DEFAULT '0',
  `intposz` float DEFAULT '0',
  `intposa` float DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `doors`
--

INSERT INTO `doors` (`ID`, `name`, `password`, `icon`, `mapicon`, `locked`, `admin`, `vip`, `faction`, `family`, `garage`, `custom`, `extvw`, `extint`, `extposx`, `extposy`, `extposz`, `extposa`, `intvw`, `intint`, `intposx`, `intposy`, `intposz`, `intposa`) VALUES
(0, 'CityHall', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2766.07, 375.556, 6.33468, 265.84, 0, 0, 2833.16, 2873.54, 320.158, 261.963),
(2, 'San Fierro Medical Center', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2655.05, 639.709, 14.4545, 186.843, 21, 21, -1439.78, -1534.99, 3001.5, 6.02194),
(3, 'Police Departement', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1605.55, 710.836, 13.8672, 359.697, 19, 19, 1385.02, 1565.7, 3001.09, 1.7234),
(5, 'DMV', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2040.91, -117.942, 35.959, 270.05, 0, 0, -2572.03, -1376.25, 1500.76, 270.597),
(6, 'Medical Center Garage', '', 19130, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, -2616.28, 686.41, 30.9219, 270.711, 21, 21, -1421.83, -1473.67, 3002.17, 90.1301),
(7, 'Fish Factory', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2085.32, 1376.54, 7.60938, 275.857, 0, 7, 1331.2, 1572.92, 3001.09, 272.724),
(9, 'Job Center', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2420.5, -723.358, 134.467, 273.953, 10, 10, 1032.76, -962.919, 1338.33, 266.892),
(10, 'RedDoor', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2425.01, 337.15, 37.0016, 235.792, 0, 11, 1384.04, -11.5931, 1001, 257.702),
(4, 'San Fiero News', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1896.05, 487.131, 35.1719, 271.796, 0, 0, -192.361, 1345.33, 1500.98, 185.995),
(33, 'Angelpine Police Station', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2161.37, -2384.76, 30.8972, 323.987, 0, 5, 322.125, 302.361, 999.148, 1.29332),
(12, 'Medical Center Basement', '', 19130, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, -2594.49, 642.18, 14.4531, 268.74, 21, 21, -1421.83, -1477.42, 3002.17, 90.4437),
(19, '[JDM] MidDay', '', 19130, 0, 0, 0, 0, -1, 5, 0, 0, 0, 0, -2544.27, 190.89, 13.0391, 84.675, 0, 17, 1368.02, -40.6749, 1000.94, 278.656),
(16, 'AP Motel', '', 19130, 0, 0, 0, 0, -1, -1, 0, 1, 0, 0, -2192.99, -2255.03, 30.696, 139.266, 0, 25, -1246.74, -182.579, 4014.65, 179.687),
(15, 'Basement', '', 19130, 0, 0, 0, 0, 0, -1, 0, 0, 19, 19, 1383.78, 1548.87, 3001.09, 356.137, 0, 0, -1594.21, 716.424, -4.90625, 274.535),
(14, 'Network Garage', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1880.88, 468.245, 35.1719, 203.146, 0, 0, -214.981, 1342.11, 1500.98, 260.481),
(17, 'OyO Rooms', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1754.33, 963.578, 24.8828, 178.746, 0, 10, -1760.15, 1109.43, -48.9885, 176.89),
(18, 'OyO Basement', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1716.55, 1018.31, 17.5859, 72.694, 0, 10, -1750.16, 1102.76, -48.9885, 86.8172),
(13, 'Medical Center Rooftop', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2695.57, 640.129, 14.4531, 178.352, 0, 0, -2642.34, 576.678, 48.6537, 179.606),
(20, 'TeePee Motel', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -767.873, 2764.97, 45.8556, 167.612, 100, 25, -1246.76, -182.002, 4014.65, 185.785),
(21, 'TeePee Motel 2', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -789.1, 2756.52, 45.8546, 277.111, 200, 25, -1246.68, -182.06, 4014.65, 178.046),
(22, 'Pier', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -911.153, 2686.26, 42.3703, 305.054, 1, 7, 1331.22, 1572.97, 3001.09, 89.8649),
(1, 'De La Valle Casino', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2492.46, 2363.2, 10.2773, 91.278, 0, 9, 36.918, 2140.73, 5.49563, 270.368),
(25, 'Drug Dealer', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1734.64, 1537.74, 7.1875, 176.95, 0, 0, 1403.82, -2446.33, 13.6728, 183.095),
(26, 'Pleasure Domes', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 2227.08, 1840.16, 10.8203, 268.174, 0, 3, -2636.82, 1402.44, 906.461, 178.612),
(27, 'San Fierro Federal Prison', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2456.15, 503.848, 30.0781, 85.9695, 0, 16, 1353.93, 1578.72, 1467.7, 359.311),
(28, '[SFN]Rooftop', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1858.56, 487.706, 108.482, 267.691, 0, 0, -212.874, 1310.46, 1507.66, 271.64),
(29, 'Tax Office', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2056.77, 454.235, 35.1719, 131.148, 0, 3, 390.77, 173.749, 1008.38, 267.785),
(30, 'Church', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -1989.9, 1117.87, 54.4688, 93.5727, 0, 1, 2229.1, -1325.06, 251.086, 359.909),
(31, 'Del Piero Cartel', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 693.553, 1967.11, 5.53906, 356.31, 0, 1, -2158.76, 642.642, 1052.38, 3.50403),
(36, 'Canteen', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 19, 19, 1394.39, 1561.94, 3001.09, 271.422, 19, 4, 460.557, -88.54, 999.555, 268.088),
(24, 'Emergency Way', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2639.27, 640.151, 14.4531, 179.714, 21, 21, -1444.81, -1498.29, 3001.51, 269.014),
(34, 'Jizzy Bar & Casino', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2624.42, 1412.17, 7.09375, 13.5732, 1, 3, -2636.74, 1403.58, 907.281, 180.289),
(35, 'La Vaquita Nocturno Bar', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -254.885, 2603.23, 62.8582, 261.753, 0, 2, 1204.69, -13.5285, 1000.92, 352.307),
(11, 'Lift Up', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 11, 1406.73, 1.164, 1001, 171.299, 0, 9, 1270.21, -33.0467, 983.223, 96.0478),
(23, 'White Taxi Company', '', 19130, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, -2463.47, 131.774, 35.1719, 131.894, 10, 3, -2027.02, -103.602, 1035.18, 174.125),
(8, '2nd Floor', '', 19130, 0, 0, 0, 0, 0, -1, 0, 0, 19, 19, 1386.95, 1548.67, 3001.09, 0.303258, 19, 19, 1386.95, 1549.02, 3004.69, 0.303258),
(32, 'Rooftop', '', 19130, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1642.29, 693.795, 38.2422, 91.8083, 19, 19, 1383.78, 1548.66, 3004.69, 355.938);

-- --------------------------------------------------------

--
-- Table structure for table `dropped`
--

CREATE TABLE `dropped` (
  `ID` int NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int DEFAULT '0',
  `itemX` float DEFAULT '0',
  `itemY` float DEFAULT '0',
  `itemZ` float DEFAULT '0',
  `itemInt` int DEFAULT '0',
  `itemWorld` int DEFAULT '0',
  `itemQuantity` int DEFAULT '0',
  `itemAmmo` int DEFAULT '0',
  `itemWeapon` int DEFAULT '0',
  `itemPlayer` varchar(24) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dropped`
--

INSERT INTO `dropped` (`ID`, `itemName`, `itemModel`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`, `itemQuantity`, `itemAmmo`, `itemWeapon`, `itemPlayer`) VALUES
(1, 'Cellphone', 18867, -2387, 746.688, 34.1156, 0, 0, 1, 0, 0, 'Havoc Redmond'),
(4, 'Fuel Can', 1650, -2650.05, 595.93, 13.5531, 0, 0, 1, 0, 0, 'vyn');

-- --------------------------------------------------------

--
-- Table structure for table `factiongarage`
--

CREATE TABLE `factiongarage` (
  `ID` int NOT NULL,
  `Faction` int NOT NULL DEFAULT '-1',
  `SpawnX` float NOT NULL DEFAULT '0',
  `SpawnY` float NOT NULL DEFAULT '0',
  `SpawnZ` float NOT NULL DEFAULT '0',
  `SpawnA` float NOT NULL DEFAULT '0',
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `factiongarage`
--

INSERT INTO `factiongarage` (`ID`, `Faction`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnA`, `PosX`, `PosY`, `PosZ`) VALUES
(1, 0, -1571.73, 712.071, -5.8822, 90.5569, -1588.1, 708.239, -5.2344),
(2, 1, -2571.85, 647.823, 14.0666, 269.85, -2565.13, 649.773, 14.4531);

-- --------------------------------------------------------

--
-- Table structure for table `factiongaragevehs`
--

CREATE TABLE `factiongaragevehs` (
  `ID` int NOT NULL,
  `Model` int NOT NULL DEFAULT '400',
  `Color1` int NOT NULL DEFAULT '0',
  `Color2` int NOT NULL DEFAULT '0',
  `Health` float NOT NULL DEFAULT '2000',
  `Damage1` int NOT NULL DEFAULT '0',
  `Damage2` int NOT NULL DEFAULT '0',
  `Damage3` int NOT NULL DEFAULT '0',
  `Damage4` int NOT NULL DEFAULT '0',
  `Garage` int NOT NULL DEFAULT '-1',
  `Spawned` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `factiongaragevehs`
--

INSERT INTO `factiongaragevehs` (`ID`, `Model`, `Color1`, `Color2`, `Health`, `Damage1`, `Damage2`, `Damage3`, `Damage4`, `Garage`, `Spawned`) VALUES
(1, 596, 0, 0, 1999.62, 16777216, 512, 0, 0, 1, 0),
(2, 416, 0, 0, 2000, 0, 0, 0, 0, 2, 0);

-- --------------------------------------------------------

--
-- Table structure for table `factions`
--

CREATE TABLE `factions` (
  `factionID` int NOT NULL,
  `factionName` varchar(32) DEFAULT NULL,
  `factionColor` int DEFAULT '0',
  `factionType` int DEFAULT '0',
  `factionRanks` int DEFAULT '0',
  `factionLockerX` float DEFAULT '0',
  `factionLockerY` float DEFAULT '0',
  `factionLockerZ` float DEFAULT '0',
  `factionLockerInt` int DEFAULT '0',
  `factionLockerWorld` int DEFAULT '0',
  `factionWeapon1` int DEFAULT '0',
  `factionAmmo1` int DEFAULT '0',
  `factionWeapon2` int DEFAULT '0',
  `factionAmmo2` int DEFAULT '0',
  `factionWeapon3` int DEFAULT '0',
  `factionAmmo3` int DEFAULT '0',
  `factionWeapon4` int DEFAULT '0',
  `factionAmmo4` int DEFAULT '0',
  `factionWeapon5` int DEFAULT '0',
  `factionAmmo5` int DEFAULT '0',
  `factionWeapon6` int DEFAULT '0',
  `factionAmmo6` int DEFAULT '0',
  `factionWeapon7` int DEFAULT '0',
  `factionAmmo7` int DEFAULT '0',
  `factionWeapon8` int DEFAULT '0',
  `factionAmmo8` int DEFAULT '0',
  `factionWeapon9` int DEFAULT '0',
  `factionAmmo9` int DEFAULT '0',
  `factionWeapon10` int DEFAULT '0',
  `factionAmmo10` int DEFAULT '0',
  `factionRank1` varchar(32) DEFAULT NULL,
  `factionRank2` varchar(32) DEFAULT NULL,
  `factionRank3` varchar(32) DEFAULT NULL,
  `factionRank4` varchar(32) DEFAULT NULL,
  `factionRank5` varchar(32) DEFAULT NULL,
  `factionRank6` varchar(32) DEFAULT NULL,
  `factionRank7` varchar(32) DEFAULT NULL,
  `factionRank8` varchar(32) DEFAULT NULL,
  `factionRank9` varchar(32) DEFAULT NULL,
  `factionRank10` varchar(32) DEFAULT NULL,
  `factionRank11` varchar(32) DEFAULT NULL,
  `factionRank12` varchar(32) DEFAULT NULL,
  `factionRank13` varchar(32) DEFAULT NULL,
  `factionRank14` varchar(32) DEFAULT NULL,
  `factionRank15` varchar(32) DEFAULT NULL,
  `factionSkin1` int DEFAULT '0',
  `factionSkin2` int DEFAULT '0',
  `factionSkin3` int DEFAULT '0',
  `factionSkin4` int DEFAULT '0',
  `factionSkin5` int DEFAULT '0',
  `factionSkin6` int DEFAULT '0',
  `factionSkin7` int DEFAULT '0',
  `factionSkin8` int DEFAULT '0',
  `factionSkin9` int NOT NULL DEFAULT '0',
  `factionSkin10` int NOT NULL DEFAULT '0',
  `SpawnX` float NOT NULL,
  `SpawnY` float NOT NULL,
  `SpawnZ` float NOT NULL,
  `SpawnInterior` int NOT NULL,
  `SpawnVW` int NOT NULL,
  `factionDurability1` int NOT NULL DEFAULT '0',
  `factionDurability2` int NOT NULL DEFAULT '0',
  `factionDurability3` int NOT NULL DEFAULT '0',
  `factionDurability4` int NOT NULL DEFAULT '0',
  `factionDurability5` int NOT NULL DEFAULT '0',
  `factionDurability6` int NOT NULL DEFAULT '0',
  `factionDurability7` int NOT NULL DEFAULT '0',
  `factionDurability8` int NOT NULL DEFAULT '0',
  `factionDurability9` int NOT NULL DEFAULT '0',
  `factionDurability10` int NOT NULL DEFAULT '0',
  `factionHighVelocity1` int NOT NULL DEFAULT '0',
  `factionHighVelocity2` int NOT NULL DEFAULT '0',
  `factionHighVelocity3` int NOT NULL DEFAULT '0',
  `factionHighVelocity4` int NOT NULL DEFAULT '0',
  `factionHighVelocity5` int NOT NULL DEFAULT '0',
  `factionHighVelocity6` int NOT NULL DEFAULT '0',
  `factionHighVelocity7` int NOT NULL DEFAULT '0',
  `factionHighVelocity8` int NOT NULL DEFAULT '0',
  `factionHighVelocity9` int NOT NULL DEFAULT '0',
  `factionHighVelocity10` int NOT NULL DEFAULT '0',
  `factionSalary1` int NOT NULL DEFAULT '0',
  `factionSalary2` int NOT NULL DEFAULT '0',
  `factionSalary3` int NOT NULL DEFAULT '0',
  `factionSalary4` int NOT NULL DEFAULT '0',
  `factionSalary5` int NOT NULL DEFAULT '0',
  `factionSalary6` int NOT NULL DEFAULT '0',
  `factionSalary7` int NOT NULL DEFAULT '0',
  `factionSalary8` int NOT NULL DEFAULT '0',
  `factionSalary9` int NOT NULL DEFAULT '0',
  `factionSalary10` int NOT NULL DEFAULT '0',
  `factionSalary11` int NOT NULL DEFAULT '0',
  `factionSalary12` int NOT NULL DEFAULT '0',
  `factionSalary13` int NOT NULL DEFAULT '0',
  `factionSalary14` int NOT NULL DEFAULT '0',
  `factionSalary15` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank1` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank2` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank3` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank4` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank5` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank6` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank7` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank8` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank9` int NOT NULL DEFAULT '0',
  `factionWeaponMinRank10` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `factions`
--

INSERT INTO `factions` (`factionID`, `factionName`, `factionColor`, `factionType`, `factionRanks`, `factionLockerX`, `factionLockerY`, `factionLockerZ`, `factionLockerInt`, `factionLockerWorld`, `factionWeapon1`, `factionAmmo1`, `factionWeapon2`, `factionAmmo2`, `factionWeapon3`, `factionAmmo3`, `factionWeapon4`, `factionAmmo4`, `factionWeapon5`, `factionAmmo5`, `factionWeapon6`, `factionAmmo6`, `factionWeapon7`, `factionAmmo7`, `factionWeapon8`, `factionAmmo8`, `factionWeapon9`, `factionAmmo9`, `factionWeapon10`, `factionAmmo10`, `factionRank1`, `factionRank2`, `factionRank3`, `factionRank4`, `factionRank5`, `factionRank6`, `factionRank7`, `factionRank8`, `factionRank9`, `factionRank10`, `factionRank11`, `factionRank12`, `factionRank13`, `factionRank14`, `factionRank15`, `factionSkin1`, `factionSkin2`, `factionSkin3`, `factionSkin4`, `factionSkin5`, `factionSkin6`, `factionSkin7`, `factionSkin8`, `factionSkin9`, `factionSkin10`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnInterior`, `SpawnVW`, `factionDurability1`, `factionDurability2`, `factionDurability3`, `factionDurability4`, `factionDurability5`, `factionDurability6`, `factionDurability7`, `factionDurability8`, `factionDurability9`, `factionDurability10`, `factionHighVelocity1`, `factionHighVelocity2`, `factionHighVelocity3`, `factionHighVelocity4`, `factionHighVelocity5`, `factionHighVelocity6`, `factionHighVelocity7`, `factionHighVelocity8`, `factionHighVelocity9`, `factionHighVelocity10`, `factionSalary1`, `factionSalary2`, `factionSalary3`, `factionSalary4`, `factionSalary5`, `factionSalary6`, `factionSalary7`, `factionSalary8`, `factionSalary9`, `factionSalary10`, `factionSalary11`, `factionSalary12`, `factionSalary13`, `factionSalary14`, `factionSalary15`, `factionWeaponMinRank1`, `factionWeaponMinRank2`, `factionWeaponMinRank3`, `factionWeaponMinRank4`, `factionWeaponMinRank5`, `factionWeaponMinRank6`, `factionWeaponMinRank7`, `factionWeaponMinRank8`, `factionWeaponMinRank9`, `factionWeaponMinRank10`) VALUES
(2, 'San Andreas Police Department', 39321, 1, 14, 1365.07, 1548.79, 3001.09, 19, 19, 3, 1, 41, 200, 43, 20, 24, 50, 25, 100, 29, 150, 31, 200, 27, 100, 34, 25, 0, 0, 'Prob Officer', 'PO I', 'PO II', 'PO III', 'PO III+I', 'Sergeant I', 'Sergeant II', 'Lieutenant', 'Captain', 'Commander', 'DCoP', 'ACoP', 'Chief of Police', 'Commissioner', 'Rank 15', 280, 281, 282, 306, 285, 286, 136, 188, 226, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 0, 1, 1, 1, 2, 3, 5, 8, 10, 10, 0),
(3, 'San Andreas Fire Medical', -8224256, 3, 15, -1443.93, -1474.53, 3001.52, 21, 21, 42, 1000, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Cadet/Intern', 'Probationary Firefighter', 'Firefighter/EMT I', 'Firefighter/EMT II', 'Firefighter/EMT III', 'DcDoctor', 'Executive Staff', 'Fire Supervisor OiT', 'Fire Captain', 'Fire Lieutenant', 'Battalion Chief', 'Deputy Fire Chief', 'Assistant Chief of Fire', 'Chief of Fire', 'Fire Commissioner', 274, 275, 276, 279, 186, 70, 308, 150, 240, 295, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(4, 'San Andreas News Network', 77361408, 2, 12, -205.36, 1307.62, 1507.64, 0, 0, 43, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Junior Staff', 'Senior Staff', 'Supervisor I', 'Supervisor II', 'Head of Operational', 'Manager Program', 'Manager Division', 'Manager Finance', 'General Manager', 'Vice CEO', 'CEO', 'Commissioner', 'Commissioner', 'Rank 14', 'Rank 15', 240, 150, 172, 295, 185, 59, 171, 187, 165, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(5, 'San Fierro Govermant Service', -793842689, 4, 10, 2854.44, 2839.94, 320.186, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Staff', 'Drive and Guard', 'Volunteer', 'Field Agent', 'Minister of Tax', 'Minister of Economy', 'Minister of Defense', 'Wise Person', 'Vice President', 'President', 'Rank 11', 'Rank 12', 'Rank 13', 'Rank 14', 'Rank 15', 295, 163, 164, 17, 59, 147, 171, 166, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(9, 'San Fierro Central Bank', -256, 3, 5, -2653.37, 684.251, 66.0938, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Rank 1', 'Rank 2', 'Rank 3', 'Rank 4', 'Rank 5', 'Rank 6', 'Rank 7', 'Rank 8', 'Rank 9', 'Rank 10', 'Rank 11', 'Rank 12', 'Rank 13', 'Rank 14', 'Rank 15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(13, 'Del Piero Cartel', -256, 5, 5, -2160.16, 646.554, 1057.59, 1, 0, 0, 0, 23, 87, 0, 0, 23, 61, 25, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Associates', 'Streetboss', 'Consiglier', 'Underboss', 'Godfather', 'Rank 6', 'Rank 7', 'Rank 8', 'Rank 9', 'Rank 10', 'Rank 11', 'Rank 12', 'Rank 13', 'Rank 14', 'Rank 15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 468, 0, 493, 445, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `factionvehicle`
--

CREATE TABLE `factionvehicle` (
  `ID` int NOT NULL,
  `Model` int NOT NULL DEFAULT '0',
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `PosA` float NOT NULL DEFAULT '0',
  `Color1` int NOT NULL DEFAULT '0',
  `Color2` int NOT NULL DEFAULT '0',
  `Faction` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `familys`
--

CREATE TABLE `familys` (
  `familyID` int NOT NULL,
  `familyName` varchar(32) DEFAULT NULL,
  `familyLeader` varchar(32) DEFAULT NULL,
  `familyMOTD` varchar(32) DEFAULT NULL,
  `familyColor` int DEFAULT '0',
  `familyLockerX` float DEFAULT '0',
  `familyLockerY` float DEFAULT '0',
  `familyLockerZ` float DEFAULT '0',
  `familyLockerInt` int DEFAULT '0',
  `familyLockerVW` int DEFAULT '0',
  `familyWeapon1` int DEFAULT '0',
  `familyAmmo1` int DEFAULT '0',
  `familyWeapon2` int DEFAULT '0',
  `familyAmmo2` int DEFAULT '0',
  `familyWeapon3` int DEFAULT '0',
  `familyAmmo3` int DEFAULT '0',
  `familyWeapon4` int DEFAULT '0',
  `familyAmmo4` int DEFAULT '0',
  `familyWeapon5` int DEFAULT '0',
  `familyAmmo5` int DEFAULT '0',
  `familyWeapon6` int DEFAULT '0',
  `familyAmmo6` int DEFAULT '0',
  `familyWeapon7` int DEFAULT '0',
  `familyAmmo7` int DEFAULT '0',
  `familyWeapon8` int DEFAULT '0',
  `familyAmmo8` int DEFAULT '0',
  `familyWeapon9` int DEFAULT '0',
  `familyAmmo9` int DEFAULT '0',
  `familyWeapon10` int DEFAULT '0',
  `familyAmmo10` int DEFAULT '0',
  `familyDurability1` int DEFAULT '0',
  `familyDurability2` int DEFAULT '0',
  `familyDurability3` int DEFAULT '0',
  `familyDurability4` int DEFAULT '0',
  `familyDurability5` int DEFAULT '0',
  `familyDurability6` int DEFAULT '0',
  `familyDurability7` int DEFAULT '0',
  `familyDurability8` int DEFAULT '0',
  `familyDurability9` int DEFAULT '0',
  `familyDurability10` int DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `familystorage`
--

CREATE TABLE `familystorage` (
  `ID` int DEFAULT '0',
  `itemID` int NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int DEFAULT '0',
  `itemQuantity` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `flat`
--

CREATE TABLE `flat` (
  `ID` int NOT NULL,
  `Owner` int NOT NULL DEFAULT '-1',
  `OwnerName` varchar(24) NOT NULL DEFAULT '_',
  `Money` int NOT NULL DEFAULT '0',
  `Price` int NOT NULL DEFAULT '0',
  `ExtPosX` float NOT NULL DEFAULT '0',
  `ExtPosY` float NOT NULL DEFAULT '0',
  `ExtPosZ` float NOT NULL DEFAULT '0',
  `IntPosX` float NOT NULL DEFAULT '0',
  `IntPosY` float NOT NULL DEFAULT '0',
  `IntPosZ` float NOT NULL DEFAULT '0',
  `IntWorld` int NOT NULL DEFAULT '0',
  `IntInterior` int NOT NULL DEFAULT '0',
  `ExtWorld` int NOT NULL DEFAULT '0',
  `ExtInterior` int NOT NULL DEFAULT '0',
  `Locked` int NOT NULL DEFAULT '0',
  `Type` int NOT NULL DEFAULT '0',
  `Weapon1` int NOT NULL DEFAULT '0',
  `Weapon2` int NOT NULL DEFAULT '0',
  `Weapon3` int NOT NULL DEFAULT '0',
  `Weapon4` int NOT NULL DEFAULT '0',
  `Weapon5` int NOT NULL DEFAULT '0',
  `Ammo1` int NOT NULL DEFAULT '0',
  `Ammo2` int NOT NULL DEFAULT '0',
  `Ammo3` int NOT NULL DEFAULT '0',
  `Ammo4` int NOT NULL DEFAULT '0',
  `Ammo5` int NOT NULL DEFAULT '0',
  `Durability1` int NOT NULL DEFAULT '0',
  `Durability2` int NOT NULL DEFAULT '0',
  `Durability3` int NOT NULL DEFAULT '0',
  `Durability4` int NOT NULL DEFAULT '0',
  `Durability5` int NOT NULL DEFAULT '0',
  `LastLogin` int NOT NULL DEFAULT '0',
  `HighVelocity1` int NOT NULL DEFAULT '0',
  `HighVelocity2` int NOT NULL DEFAULT '0',
  `HighVelocity3` int NOT NULL DEFAULT '0',
  `HighVelocity4` int NOT NULL DEFAULT '0',
  `HighVelocity5` int NOT NULL DEFAULT '0',
  `TaxState` int NOT NULL DEFAULT '0',
  `TaxDate` int NOT NULL DEFAULT '0',
  `TaxPaid` int NOT NULL DEFAULT '0',
  `FurnitureLevel` int NOT NULL DEFAULT '1',
  `Sealed` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `flatkeys`
--

CREATE TABLE `flatkeys` (
  `ID` int NOT NULL,
  `PlayerID` int NOT NULL DEFAULT '-1',
  `FlatID` int NOT NULL DEFAULT '-1',
  `Name` varchar(24) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `flatstorage`
--

CREATE TABLE `flatstorage` (
  `ID` int DEFAULT '0',
  `itemID` int NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int DEFAULT '0',
  `itemQuantity` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `flat_queue`
--

CREATE TABLE `flat_queue` (
  `ID` int NOT NULL,
  `Username` varchar(24) NOT NULL,
  `FlatID` int NOT NULL DEFAULT '0',
  `Message` varchar(128) NOT NULL DEFAULT 'idk'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `fuelpump`
--

CREATE TABLE `fuelpump` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `PosA` float NOT NULL DEFAULT '0',
  `Fuel` float NOT NULL DEFAULT '100',
  `Business` int NOT NULL DEFAULT '-1'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `furniture`
--

CREATE TABLE `furniture` (
  `ID` int DEFAULT '0',
  `furnitureID` int NOT NULL,
  `furnitureName` varchar(32) DEFAULT NULL,
  `furnitureModel` int DEFAULT '0',
  `furnitureX` float DEFAULT '0',
  `furnitureY` float DEFAULT '0',
  `furnitureZ` float DEFAULT '0',
  `furnitureRX` float DEFAULT '0',
  `furnitureRY` float DEFAULT '0',
  `furnitureRZ` float DEFAULT '0',
  `furnitureType` int DEFAULT '0',
  `furnitureWorld` int NOT NULL DEFAULT '0',
  `furnitureInterior` int NOT NULL DEFAULT '0',
  `TextureModelID` int NOT NULL DEFAULT '0',
  `TextureTXD` varchar(24) NOT NULL DEFAULT 'NoTexture',
  `TextureName` varchar(24) NOT NULL DEFAULT 'NoTexture'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `garage`
--

CREATE TABLE `garage` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `gaterequests`
--

CREATE TABLE `gaterequests` (
  `ID` int NOT NULL,
  `Name` varchar(25) NOT NULL,
  `Date` varchar(26) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `gates`
--

CREATE TABLE `gates` (
  `gateID` int NOT NULL,
  `gateModel` int DEFAULT '0',
  `gateSpeed` float DEFAULT '0',
  `gateTime` int DEFAULT '0',
  `gateX` float DEFAULT '0',
  `gateY` float DEFAULT '0',
  `gateZ` float DEFAULT '0',
  `gateRX` float DEFAULT '0',
  `gateRY` float DEFAULT '0',
  `gateRZ` float DEFAULT '0',
  `gateInterior` int DEFAULT '0',
  `gateWorld` int DEFAULT '0',
  `gateMoveX` float DEFAULT '0',
  `gateMoveY` float DEFAULT '0',
  `gateMoveZ` float DEFAULT '0',
  `gateMoveRX` float DEFAULT '0',
  `gateMoveRY` float DEFAULT '0',
  `gateMoveRZ` float DEFAULT '0',
  `gateLinkID` int DEFAULT '0',
  `gateFaction` int DEFAULT '0',
  `gatePass` varchar(32) DEFAULT NULL,
  `gateRadius` float DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `housekeys`
--

CREATE TABLE `housekeys` (
  `ID` int NOT NULL,
  `HouseID` int NOT NULL DEFAULT '-1',
  `PlayerID` int NOT NULL DEFAULT '-1',
  `Name` varchar(24) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `houses`
--

CREATE TABLE `houses` (
  `houseID` int NOT NULL,
  `houseOwner` int DEFAULT '0',
  `housePrice` int DEFAULT '0',
  `housePosX` float DEFAULT '0',
  `housePosY` float DEFAULT '0',
  `housePosZ` float DEFAULT '0',
  `housePosA` float DEFAULT '0',
  `houseIntX` float DEFAULT '0',
  `houseIntY` float DEFAULT '0',
  `houseIntZ` float DEFAULT '0',
  `houseIntA` float DEFAULT '0',
  `houseInterior` int DEFAULT '0',
  `houseExterior` int DEFAULT '0',
  `houseExteriorVW` int DEFAULT '0',
  `houseLocked` int DEFAULT '0',
  `houseWeapon1` int DEFAULT '0',
  `houseAmmo1` int DEFAULT '0',
  `houseWeapon2` int DEFAULT '0',
  `houseAmmo2` int DEFAULT '0',
  `houseWeapon3` int DEFAULT '0',
  `houseAmmo3` int DEFAULT '0',
  `houseWeapon4` int DEFAULT '0',
  `houseAmmo4` int DEFAULT '0',
  `houseWeapon5` int DEFAULT '0',
  `houseAmmo5` int DEFAULT '0',
  `houseWeapon6` int DEFAULT '0',
  `houseAmmo6` int DEFAULT '0',
  `houseWeapon7` int DEFAULT '0',
  `houseAmmo7` int DEFAULT '0',
  `houseWeapon8` int DEFAULT '0',
  `houseAmmo8` int DEFAULT '0',
  `houseWeapon9` int DEFAULT '0',
  `houseAmmo9` int DEFAULT '0',
  `houseWeapon10` int DEFAULT '0',
  `houseAmmo10` int DEFAULT '0',
  `houseMoney` int DEFAULT '0',
  `houseOwnerName` varchar(32) NOT NULL DEFAULT 'No owner',
  `houseDurability1` int NOT NULL DEFAULT '0',
  `houseDurability2` int NOT NULL DEFAULT '0',
  `houseDurability3` int NOT NULL DEFAULT '0',
  `houseDurability4` int NOT NULL DEFAULT '0',
  `houseDurability5` int NOT NULL DEFAULT '0',
  `houseDurability6` int NOT NULL DEFAULT '0',
  `houseDurability7` int NOT NULL DEFAULT '0',
  `houseDurability8` int NOT NULL DEFAULT '0',
  `houseDurability9` int NOT NULL DEFAULT '0',
  `houseDurability10` int NOT NULL DEFAULT '0',
  `houseSerial1` int NOT NULL DEFAULT '0',
  `houseSerial2` int NOT NULL DEFAULT '0',
  `houseSerial3` int NOT NULL DEFAULT '0',
  `houseSerial4` int NOT NULL DEFAULT '0',
  `houseSerial5` int NOT NULL DEFAULT '0',
  `houseSerial6` int NOT NULL DEFAULT '0',
  `houseSerial7` int NOT NULL DEFAULT '0',
  `houseSerial8` int NOT NULL DEFAULT '0',
  `houseSerial9` int NOT NULL DEFAULT '0',
  `houseSerial10` int NOT NULL DEFAULT '0',
  `houseHighVelocity1` int NOT NULL DEFAULT '0',
  `houseHighVelocity2` int NOT NULL DEFAULT '0',
  `houseHighVelocity3` int NOT NULL DEFAULT '0',
  `houseHighVelocity4` int NOT NULL DEFAULT '0',
  `houseHighVelocity5` int NOT NULL DEFAULT '0',
  `houseHighVelocity6` int NOT NULL DEFAULT '0',
  `houseHighVelocity7` int NOT NULL DEFAULT '0',
  `houseHighVelocity8` int NOT NULL DEFAULT '0',
  `houseHighVelocity9` int NOT NULL DEFAULT '0',
  `houseHighVelocity10` int NOT NULL DEFAULT '0',
  `housePark` int NOT NULL DEFAULT '0',
  `houseParkX` float NOT NULL DEFAULT '0',
  `houseParkY` float NOT NULL DEFAULT '0',
  `houseParkZ` float NOT NULL DEFAULT '0',
  `houseVehInside` int NOT NULL DEFAULT '0',
  `houseType` int NOT NULL DEFAULT '1',
  `LastLogin` int NOT NULL DEFAULT '0',
  `TaxPaid` int NOT NULL DEFAULT '0',
  `TaxDate` int NOT NULL DEFAULT '0',
  `TaxState` int NOT NULL DEFAULT '0',
  `FurnitureLevel` int NOT NULL DEFAULT '1',
  `houseSealed` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `housestorage`
--

CREATE TABLE `housestorage` (
  `ID` int DEFAULT '0',
  `itemID` int NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int DEFAULT '0',
  `itemQuantity` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `house_queue`
--

CREATE TABLE `house_queue` (
  `ID` int NOT NULL,
  `Username` varchar(24) NOT NULL DEFAULT '',
  `HouseID` int NOT NULL DEFAULT '0',
  `Message` varchar(128) NOT NULL DEFAULT 'idk'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `inventory`
--

CREATE TABLE `inventory` (
  `ID` int DEFAULT '0',
  `invID` int NOT NULL,
  `invItem` varchar(32) DEFAULT NULL,
  `invModel` int DEFAULT '0',
  `invQuantity` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `inventory`
--

INSERT INTO `inventory` (`ID`, `invID`, `invItem`, `invModel`, `invQuantity`) VALUES
(2, 2, 'GPS', 18875, 1),
(2, 3, 'Cellphone', 18867, 1),
(2, 4, 'Portable Radio', 19942, 1),
(1, 5, 'Component', 19627, 1000),
(1, 6, 'Promethazine', 2709, 1);

-- --------------------------------------------------------

--
-- Table structure for table `object`
--

CREATE TABLE `object` (
  `mobjID` int NOT NULL,
  `mobjModel` int NOT NULL DEFAULT '980',
  `mobjInterior` int NOT NULL DEFAULT '0',
  `mobjWorld` int NOT NULL DEFAULT '0',
  `mobjX` float NOT NULL DEFAULT '0',
  `mobjY` float NOT NULL DEFAULT '0',
  `mobjZ` float NOT NULL DEFAULT '0',
  `mobjRX` float NOT NULL DEFAULT '0',
  `mobjRY` float NOT NULL DEFAULT '0',
  `mobjRZ` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `object`
--

INSERT INTO `object` (`mobjID`, `mobjModel`, `mobjInterior`, `mobjWorld`, `mobjX`, `mobjY`, `mobjZ`, `mobjRX`, `mobjRY`, `mobjRZ`) VALUES
(66, 1223, 0, 0, 2288.42, 522.77, -0.0956, 0, 0, 15.6326),
(68, 1280, 0, 0, 2290.32, 523.209, 1.2043, 0, 0, 89.768),
(79, 3657, 0, 0, -1609.18, 678.063, 6.6974, 0, 0, -0.0232);

-- --------------------------------------------------------

--
-- Table structure for table `parks`
--

CREATE TABLE `parks` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `Interior` int NOT NULL DEFAULT '0',
  `World` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `playersalary`
--

CREATE TABLE `playersalary` (
  `id` int NOT NULL,
  `owner` int NOT NULL DEFAULT '-1',
  `name` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `amount` int NOT NULL DEFAULT '0',
  `date` varchar(40) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `playersalary`
--

INSERT INTO `playersalary` (`id`, `owner`, `name`, `amount`, `date`) VALUES
(1, 2, 'Street Sweeper', 4000, '2023-07-09 20:16:23');

-- --------------------------------------------------------

--
-- Table structure for table `playerucp`
--

CREATE TABLE `playerucp` (
  `pID` int NOT NULL,
  `UCP` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL DEFAULT 'none@gmail.com',
  `DiscordID` bigint NOT NULL DEFAULT '0',
  `DiscordCode` int NOT NULL DEFAULT '0',
  `Password` varchar(255) NOT NULL DEFAULT 'nopassword',
  `code` mediumint NOT NULL DEFAULT '0',
  `regdate` varchar(50) NOT NULL DEFAULT 'notyet',
  `nohp` varchar(15) NOT NULL DEFAULT '0869',
  `hide` varchar(100) NOT NULL DEFAULT 'true',
  `Banned` int NOT NULL DEFAULT '0',
  `BannedBy` varchar(24) NOT NULL DEFAULT 'Admin',
  `BannedReason` varchar(32) NOT NULL DEFAULT 'Undefined',
  `BannedTime` int NOT NULL DEFAULT '0',
  `Admin` int NOT NULL DEFAULT '0',
  `Registered` int NOT NULL DEFAULT '0',
  `Active` int NOT NULL DEFAULT '0',
  `LastIP` varchar(26) NOT NULL DEFAULT '127.0.0.1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `playerucp`
--

INSERT INTO `playerucp` (`pID`, `UCP`, `email`, `DiscordID`, `DiscordCode`, `Password`, `code`, `regdate`, `nohp`, `hide`, `Banned`, `BannedBy`, `BannedReason`, `BannedTime`, `Admin`, `Registered`, `Active`, `LastIP`) VALUES
(1, 'vyn', '', 784643292788817931, 12345, '$2y$12$CDxmYZ..FeBSjOhZz1Q7qe7hKpFDiMlFR8.8g.TdzXB/lmXso2Olq', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 7, 1688905314, 1, '180.252.93.186'),
(2, 'Luckystar', '', 852706243221913651, 123, '$2y$12$q9tAw1Kjp/nSNTFs3MNizOHUHhvd31mqXva6kMIsNqmIvpqT4xXNm', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 7, 1688907926, 1, '158.140.175.162'),
(3, 'Galang', '', 1029770371634831390, 123, '', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 5, 1646307653, 0, '127.0.0.1'),
(4, 'KNTLMNS', 'lanaiskhaq@gmail.com\r\n', 462981913360072714, 123, '$2y$12$bVJkyUqMsrUaurILGQ/5M.WXMhT8oNhJJbz1w62PIXYWgbCrUoM4y', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 5, 1689344387, 1, '36.79.74.219'),
(5, 'yanto123', '', 1029770371634831390, 123, '', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 5, 1646307653, 0, '127.0.0.1'),
(6, 'Puur', '', 451731994968326164, 123, '$2y$12$JzzNDvFbY69anM0dcgI.u.Z8xteuZh/pfijYvktN124Hx5DJRd1Uq', 0, 'None', '', 'true', 0, 'Admin', 'Undefined', 0, 7, 1689426581, 1, '127.0.0.1'),
(7, 'Anura', 'anwarfauzan75@gmail.com', 0, 0, '$2y$10$tzOOvxqM9YwZKMGbEvsRUO1ZwAuhy9A9VllCswET.Bmm.gjzQllbW', 0, 'notyet', '0869', 'true', 0, 'Admin', 'Undefined', 0, 7, 1689442899, 1, '103.111.102.58'),
(8, 'budi123', 'galanggeming3@gmail.com', 0, 0, '$2y$10$Oq0vdepkv58OnZDljS4PI.slmyw4GpJM3sUKERpsT3KCae3Xn32PC', 0, 'notyet', '0869', 'true', 0, 'Admin', 'Undefined', 0, 0, 1689442997, 1, '36.73.32.82'),
(9, 'LuminouZ', 'gakira340@gmail.com', 0, 0, '$2y$10$9qD/42s/MVEsTO5VSBX2sOf4xg7WQXOmke0wBVQ4Tqr83k6RCJFS.', 0, 'notyet', '0869', 'true', 0, 'Admin', 'Undefined', 0, 0, 1689444301, 1, '127.0.0.1');

-- --------------------------------------------------------

--
-- Table structure for table `race_cps`
--

CREATE TABLE `race_cps` (
  `ID` int NOT NULL,
  `RaceID` int NOT NULL DEFAULT '0',
  `Type` int NOT NULL DEFAULT '0',
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `CPIndex` varchar(16) NOT NULL DEFAULT 'Index_Null'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `race_list`
--

CREATE TABLE `race_list` (
  `ID` int NOT NULL,
  `OwnerID` int NOT NULL DEFAULT '0',
  `RaceName` varchar(24) NOT NULL DEFAULT 'Noname',
  `CreationDate` varchar(26) NOT NULL DEFAULT '01/01/1999'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `rental`
--

CREATE TABLE `rental` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `SpawnX` float NOT NULL DEFAULT '0',
  `SpawnY` float NOT NULL DEFAULT '0',
  `SpawnZ` float NOT NULL DEFAULT '0',
  `SpawnA` float NOT NULL DEFAULT '0',
  `Vehicle1` int NOT NULL DEFAULT '0',
  `Vehicle2` int NOT NULL DEFAULT '0',
  `Price1` int NOT NULL DEFAULT '0',
  `Price2` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `rock`
--

CREATE TABLE `rock` (
  `ID` int NOT NULL,
  `RockX` float NOT NULL DEFAULT '0',
  `RockY` float NOT NULL DEFAULT '0',
  `RockZ` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `rock`
--

INSERT INTO `rock` (`ID`, `RockX`, `RockY`, `RockZ`) VALUES
(12, -1312.14, 2518.05, 86.3651),
(58, -1280.42, 2569.43, 87.8832),
(60, -1279.58, 2567.67, 88.1201),
(61, -1281.58, 2568, 87.7355),
(62, -1267.53, 2570.07, 93.1049),
(63, -1265.68, 2571.95, 92.9102),
(64, -1265.67, 2569.44, 93.2757),
(65, -1279.62, 2585.88, 95.1425),
(66, -1282.01, 2585.64, 95.1466),
(67, -1280.63, 2583.8, 95.5258),
(68, -1257.8, 2564.49, 92.7658),
(71, -1301.8, 2585.93, 87.9897),
(72, -1303.3, 2584.24, 87.8597),
(73, -1300.27, 2584.13, 88.1136),
(74, -1295.53, 2572.13, 84.426),
(75, -1293.85, 2570.72, 84.769),
(76, -1296.45, 2570.04, 84.5097),
(77, -1315.08, 2582.81, 85.1896),
(78, -1314.16, 2584.66, 85.9857),
(79, -1312.56, 2582.64, 85.6044),
(80, -1321.8, 2580.27, 80.0967),
(81, -1323.84, 2581.14, 79.1649),
(82, -1326.93, 2579.29, 79.73),
(83, -1328.04, 2577.04, 80.1608),
(84, -1331.15, 2573.84, 80.9036),
(85, -1331.72, 2560.18, 87.6628),
(86, -1332.04, 2564.82, 87.5828),
(87, -1333.37, 2562.6, 87.5628),
(88, -1328.57, 2562.47, 87.7028),
(120, -1300.68, 2547.48, 86.6922),
(121, -1260.07, 2561.94, 91.5988),
(122, -1258.11, 2562.7, 92.1822);

-- --------------------------------------------------------

--
-- Table structure for table `samacc`
--

CREATE TABLE `samacc` (
  `ID` int NOT NULL,
  `Username` varchar(24) NOT NULL,
  `Password` varchar(32) NOT NULL,
  `Created` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `speedcameras`
--

CREATE TABLE `speedcameras` (
  `speedID` int NOT NULL,
  `speedRange` float DEFAULT '0',
  `speedLimit` float DEFAULT '0',
  `speedX` float DEFAULT '0',
  `speedY` float DEFAULT '0',
  `speedZ` float DEFAULT '0',
  `speedAngle` float DEFAULT '0',
  `speedvehicle` int NOT NULL DEFAULT '0',
  `speedplate` varchar(32) NOT NULL,
  `speedTime` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `speedcameras`
--

INSERT INTO `speedcameras` (`speedID`, `speedRange`, `speedLimit`, `speedX`, `speedY`, `speedZ`, `speedAngle`, `speedvehicle`, `speedplate`, `speedTime`) VALUES
(2, 50, 120, -2021.72, 1280.35, 5.9875, 262.781, 426, 'NONE', 1688160985),
(3, 50, 120, -1573.72, 952.306, 5.9875, 33.4718, 562, 'NONE', 1688893476),
(4, 50, 80, -1612.06, 453.731, 5.9764, 132.547, 587, 'NONE', 1688902240),
(6, 30, 60, -2014.15, 207.083, 26.4875, 180.93, 562, 'NONE', 1689437417),
(7, 30, 50, -2216.65, -62.9408, 34.1203, 90.3609, 477, 'NONE', 1688029119),
(8, 40, 80, -2668.16, 2049.72, 55.8209, 95.3639, 470, '6FUR118', 1669785594);

-- --------------------------------------------------------

--
-- Table structure for table `tags`
--

CREATE TABLE `tags` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `RotX` float NOT NULL DEFAULT '0',
  `RotY` float NOT NULL DEFAULT '0',
  `RotZ` float NOT NULL DEFAULT '0',
  `Font` varchar(24) NOT NULL DEFAULT 'Arial',
  `Text` varchar(64) NOT NULL DEFAULT 'None',
  `Size` int NOT NULL DEFAULT '24',
  `Interior` int NOT NULL DEFAULT '-1',
  `World` int NOT NULL DEFAULT '-1',
  `Bold` int NOT NULL DEFAULT '0',
  `Owner` int NOT NULL DEFAULT '-1',
  `Color` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `tickets`
--

CREATE TABLE `tickets` (
  `ID` int DEFAULT '0',
  `ticketID` int NOT NULL,
  `ticketFee` int DEFAULT '0',
  `ticketBy` varchar(24) DEFAULT NULL,
  `ticketDate` varchar(36) DEFAULT NULL,
  `ticketReason` varchar(32) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `toys`
--

CREATE TABLE `toys` (
  `Id` int NOT NULL,
  `Owner` varchar(40) NOT NULL DEFAULT '',
  `Slot0_Model` int NOT NULL DEFAULT '0',
  `Slot0_Bone` int NOT NULL DEFAULT '0',
  `Slot0_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_Model` int NOT NULL DEFAULT '0',
  `Slot1_Bone` int NOT NULL DEFAULT '0',
  `Slot1_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot1_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_Model` int NOT NULL DEFAULT '0',
  `Slot2_Bone` int NOT NULL DEFAULT '0',
  `Slot2_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot2_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_Model` int NOT NULL DEFAULT '0',
  `Slot3_Bone` int NOT NULL DEFAULT '0',
  `Slot3_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot3_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_Model` int NOT NULL DEFAULT '0',
  `Slot4_Bone` int NOT NULL DEFAULT '0',
  `Slot4_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot4_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_Model` int NOT NULL DEFAULT '0',
  `Slot5_Bone` int NOT NULL DEFAULT '0',
  `Slot5_XPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_YPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_ZPos` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_XRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_YRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_ZRot` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_XScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_YScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot5_ZScale` float(20,3) NOT NULL DEFAULT '0.000',
  `Slot0_Toggle` int NOT NULL DEFAULT '0',
  `Slot1_Toggle` int NOT NULL DEFAULT '0',
  `Slot2_Toggle` int NOT NULL DEFAULT '0',
  `Slot3_Toggle` int NOT NULL DEFAULT '0',
  `Slot4_Toggle` int NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `trash`
--

CREATE TABLE `trash` (
  `TrashID` int NOT NULL,
  `TrashType` int NOT NULL,
  `TrashX` float NOT NULL,
  `TrashY` float NOT NULL,
  `TrashZ` float NOT NULL,
  `TrashRotX` float NOT NULL,
  `TrashRotY` float NOT NULL,
  `TrashRotZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `trash`
--

INSERT INTO `trash` (`TrashID`, `TrashType`, `TrashX`, `TrashY`, `TrashZ`, `TrashRotX`, `TrashRotY`, `TrashRotZ`) VALUES
(2, 1, -2506.78, -184.789, 25.1796, 0, 0, 90.4906),
(4, 1, -2701.28, -186.817, 3.90676, 0, 0, 91.4609),
(5, 2, -2510.78, -105.322, 24.7308, 0, 0, 89.9808),
(6, 2, -1850.06, -166.784, 8.21669, 0, 0, 0.13472),
(7, 1, -2018.85, -101.786, 34.7041, 0, 0, 182.14),
(8, 2, -1980.72, 151.948, 26.7875, 0, 0, -90.8327),
(9, 2, -1980.69, 111.658, 26.7775, 0, 0, -90.5727),
(10, 1, -2856, 509.037, 4.31406, 0, 0, -1.45521),
(11, 2, -2848.17, 413.794, 3.54936, 0, 0, -89.8326),
(12, 1, -2695.6, 260.154, 4.20281, 0, 0, 178.067),
(13, 1, -2694.58, 260.099, 4.17281, 0, 0, 179.573),
(14, 2, -2581.28, 335.49, 4.21295, 0, 0, 268.621),
(15, 2, -2617.3, 616.425, 13.5831, 0, 0, 270.524),
(16, 1, -2629.67, 697.805, 27.5191, 0, 0, 179.657),
(17, 2, -2629.43, 825.415, 49.081, 0, 0, 1.70502),
(18, 2, -2711.56, 790.521, 49.0848, 0, 0, 267.391),
(19, 1, -2767.74, 779.994, 52.2913, 0, 0, 89.6525),
(20, 2, -2855.48, 794.462, 36.0534, 0.6, 12.2, 253.001),
(21, 2, -2819.84, 968.039, 43.1363, 0, 0, -53.2823),
(22, 1, -2865.95, 1081.32, 30.7158, 0, 0, -61.1958),
(23, 2, -2704.74, 1306.94, 6.09171, 0, 0, 266.137),
(24, 2, -2632.81, 1400.17, 6.19375, 0, 0, 13.5316),
(25, 2, -2507.69, 1229.35, 36.5083, 0, 0, 334.734),
(26, 2, -2519.78, 1164.8, 54.4991, 0, 0, 356.958),
(27, 2, -2400.87, 1154.26, 54.4869, 0, 0, 343.484),
(28, 2, -2266.29, 1273.63, 41.725, 0, 2.8, 27.375),
(29, 2, -2059.13, 1334.22, 6.19485, 0, 0, 359.488),
(30, 1, -1716.33, 1366.55, 6.73687, 0, 0, 221.62),
(31, 1, -1670.3, 1337.76, 6.7375, 0, 0, 43.0419),
(32, 2, -1714.32, 1207.15, 24.2049, 0, 0, 44.4919),
(33, 2, -1726.22, 1064.6, 44.2625, 0, 0, 89.3923),
(34, 2, -1703.12, 707.905, 23.9644, 0, 0, 272.067),
(35, 2, -1770.75, 593.973, 28.0428, 0, -10.4, 180.259),
(36, 2, -2012.71, 519.466, 34.2651, 0, 0, 88.2457),
(37, 2, -1910.07, 300.05, 40.0969, 0, 0, 267.054),
(38, 2, -1652.64, 455.388, 6.29969, 0, 0, -47.0054),
(39, 2, -1725.22, 90.7144, 2.61469, 0, 0, -132.66),
(40, 2, -1844.48, -14.8525, 14.1672, 0, 0, 87.9325),
(41, 2, -2039.33, 20.7179, 34.4119, 0, 0, 178.693),
(43, 2, -2293.08, 40.5195, 34.3941, 0, 0, 178.09),
(44, 2, -2429.99, 3.04886, 34.3919, 0, 0, 90.2292),
(45, 2, -2303.73, -116.623, 34.4203, 0, 0, 356.065),
(46, 2, -1983.67, 181.19, 26.8158, 0, 0, -94.3557),
(48, 2, -2236.32, 225.195, 34.2992, 0, 0, 270.27),
(49, 2, -2169.06, 276.474, 34.3158, 0, 0, 268.657),
(50, 2, -1995.5, -244.724, 34.8703, 0, 0, -92.6342);

-- --------------------------------------------------------

--
-- Table structure for table `tree`
--

CREATE TABLE `tree` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `PosRX` float NOT NULL DEFAULT '0',
  `PosRY` float NOT NULL DEFAULT '0',
  `PosRZ` float NOT NULL DEFAULT '0',
  `Time` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tree`
--

INSERT INTO `tree` (`ID`, `PosX`, `PosY`, `PosZ`, `PosRX`, `PosRY`, `PosRZ`, `Time`) VALUES
(57, -1551.68, -1378.14, 49.6079, 0, 0, 164.51, 0),
(58, -1688.37, -1217, 57.7924, 0, 0, 179.527, 0),
(59, -1739.17, -1089.54, 70.3683, 0, 0, 2.70942, 0),
(60, -1758.56, -977.591, 74.9583, 0, 0, 1.21531, 0),
(61, -1680.13, -950.255, 66.5791, 0, 0, 185.41, 0),
(62, -1725.18, -888.682, 72.1022, 0, 0, 148.703, 0),
(63, -2232.92, -803.38, 59.3067, 0, 0, 51.859, 0),
(64, -2309.37, -855.018, 37.6599, 0, 0, 42.4588, 0),
(65, -2271.31, -1051.48, 14.8355, 0, 0, 145.546, 0),
(66, -2195.83, -1146.28, 14.8725, 0, 0, 256.227, 0),
(67, -1916.29, -1494.28, 21.4799, 0, 0, 101.053, 0),
(68, -1944.38, -1467.36, 18.4928, 0, 0, 44.6288, 0),
(69, -2571.69, -918.036, 14.8736, 0, 0, 129.543, 0),
(70, -2534.26, -963.198, 22.0976, 0, 0, 238.897, 0),
(71, -2415.39, -963.291, 14.5341, 0, 0, 190.066, 0),
(72, -2382.4, -984.365, 14.875, 0, 0, 262.374, 0),
(73, -1892.59, 2561.24, 47.7838, 0, 0, 347.265, 0),
(74, -1801.94, 2708.77, 55.9845, 0, 0, 238.947, 0),
(75, -1924.36, 2728.06, 90.3501, 0, 0, 117.926, 0),
(76, -2040.67, 2472.91, 48.4884, 0, 0, 3.58228, 0),
(77, -2084.22, 2488.76, 51.4563, 0, 0, 352.856, 0),
(78, -2895.23, 908.552, 4.78911, 0, 0, 332.249, 0),
(79, -2934.56, 739.165, 5.26761, 0, 0, 116.36, 0),
(80, -2880.08, 620.442, 5.70844, 0, 0, 257.651, 0),
(81, -2606.29, -2197.06, 25.6108, 0, 0, 306.218, 0),
(82, -2496.15, -2585.85, 69.4524, 0, 0, 188.404, 0),
(83, -2507.08, -2614.71, 64.5644, 0, 0, 138.897, 0),
(84, -2295.01, -2716.7, 43.2836, 0, 0, 92.5232, 0),
(85, -2064.23, -2772.08, 45.4602, 0, 0, 273.945, 0),
(86, -1778.94, -2469.63, 16.2024, 0, 0, 316.535, 0),
(87, -1747.7, -2469.72, 16.657, 0, 0, 289.902, 0),
(88, -1565.2, -2436.57, 46.3435, 0, 0, 20.746, 0),
(89, -1444.55, -2351.93, 17.9907, 0, 0, 131.354, 0),
(90, -1632.67, -2195.53, 29.483, 0, 0, 203.445, 0),
(91, -1525.46, -2045.21, 46.6197, 0, 0, 30.7963, 0),
(92, -1851.19, -1994.57, 83.1561, 0, 0, 89.3901, 0),
(93, -1736.34, -1947.37, 98.3715, 0, 0, 315.306, 0),
(94, -1541.08, -1789.02, 55.2415, 0, 0, 36.7262, 0),
(95, -2063.54, -2104.99, 57.4227, 0, 0, 24.5296, 0),
(96, -1991.4, -1818.42, 39.8967, 0, 0, 47.789, 0),
(97, -1949.91, -1700.9, 25.3328, 0, 0, 305.256, 0),
(98, -1605.6, -1561.63, 34.5566, 0, 0, 125.424, 0),
(99, -1877.12, -1351.81, 34.5013, 0, 0, 340.953, 0),
(100, -1813.87, -1334.71, 31.3564, 0, 0, 316.849, 0),
(101, -1826.87, -1065.87, 59.6097, 0, 0, 199.638, 0),
(102, -1865.3, -1055.25, 29.5979, 0, 0, 118.628, 0),
(103, -1899.26, -2481.89, 32.3323, 0, 0, 6.0193, 0),
(104, -2214.71, -2526.8, 29.7149, 0, 0, 103.467, 0),
(105, -2334.26, -2405.12, 24.4395, 0, 0, 138.874, 0),
(107, -2423.57, -698.674, 132.178, 0, 0, 7.42814, 0),
(108, -1315.21, -1224.13, 129.747, 0, 0, 300.59, 0),
(109, -1288.75, -1203.84, 128.28, 0, 0, 356.677, 0),
(110, -1564.66, -1096.83, 136.212, 0, 0, 210.059, 0),
(111, -1599.73, -1056.21, 129.781, 0, 0, 54.3307, 0),
(112, -1532.73, -953.623, 180.951, 0, 0, 63.1041, 0),
(113, -1535.79, -928.131, 182.956, 0, 0, 340.383, 0),
(114, -1443.46, -960.818, 200.367, 0, 0, 170.265, 0),
(115, -1446.5, -922.422, 201.13, 0, 0, 284.609, 0),
(116, -1368.69, -942.718, 197.663, 0, 0, 251.709, 0),
(117, -1326.86, -967.4, 193.239, 0, 0, 243.876, 0),
(118, -1303.34, -960.602, 186.125, 0, 0, 328.14, 0),
(119, -1004.55, -501.8, 29.4317, 0, 0, 150.165, 0),
(120, -1007.82, -555.363, 31.1778, 0, 0, 161.132, 0),
(121, -1133.66, -627.796, 31.1078, 0, 0, 157.998, 0),
(122, -1139.54, -718.33, 31.2126, 0, 0, 183.692, 0),
(123, -1292.83, -774.919, 68.8362, 0, 0, 19.8171, 0),
(124, -1940.71, -618.508, 23.7901, 0, 0, 194.949, 0),
(125, -1939.87, -660.445, 23.7637, 0, 0, 181.475, 0),
(126, -2137.75, -665.092, 47.4383, 0, 0, 259.472, 0),
(127, -2893.72, -788.939, 7.04187, 0, 0, 186.802, 0),
(128, -2764.21, -657.003, 40.0507, 0, 0, 228.476, 0);

-- --------------------------------------------------------

--
-- Table structure for table `vehicle`
--

CREATE TABLE `vehicle` (
  `vehID` int NOT NULL,
  `vehModel` int NOT NULL DEFAULT '0',
  `vehExtraID` int NOT NULL DEFAULT '-1',
  `vehX` float NOT NULL DEFAULT '0',
  `vehY` float NOT NULL DEFAULT '0',
  `vehZ` float NOT NULL DEFAULT '0',
  `vehA` float NOT NULL DEFAULT '0',
  `vehColor1` int NOT NULL DEFAULT '0',
  `vehColor2` int NOT NULL DEFAULT '0',
  `vehWorld` int NOT NULL DEFAULT '0',
  `vehInterior` int NOT NULL DEFAULT '0',
  `vehFuel` int NOT NULL DEFAULT '0',
  `vehDamage1` int NOT NULL DEFAULT '0',
  `vehDamage2` int NOT NULL DEFAULT '0',
  `vehDamage3` int NOT NULL DEFAULT '0',
  `vehDamage4` int NOT NULL DEFAULT '0',
  `vehHealth` int NOT NULL DEFAULT '1000',
  `vehInsurance` int NOT NULL DEFAULT '0',
  `vehInsuTime` int NOT NULL DEFAULT '0',
  `vehLocked` int NOT NULL DEFAULT '0',
  `vehPlate` varchar(16) NOT NULL DEFAULT 'NONE',
  `vehRental` int NOT NULL DEFAULT '-1',
  `vehRentalTime` int NOT NULL DEFAULT '0',
  `vehInsuranced` int NOT NULL DEFAULT '0',
  `vehHouse` int NOT NULL DEFAULT '-1',
  `vehPark` int NOT NULL DEFAULT '-1',
  `vehWood` int NOT NULL DEFAULT '0',
  `toyid0` int NOT NULL DEFAULT '0',
  `toyid1` int NOT NULL DEFAULT '0',
  `toyid2` int NOT NULL DEFAULT '0',
  `toyid3` int NOT NULL DEFAULT '0',
  `toyid4` int NOT NULL DEFAULT '0',
  `toyposx0` float NOT NULL DEFAULT '0',
  `toyposx1` float NOT NULL DEFAULT '0',
  `toyposx2` float NOT NULL DEFAULT '0',
  `toyposx3` float NOT NULL DEFAULT '0',
  `toyposx4` float NOT NULL DEFAULT '0',
  `toyposy0` float NOT NULL DEFAULT '0',
  `toyposy1` float NOT NULL DEFAULT '0',
  `toyposy2` float NOT NULL DEFAULT '0',
  `toyposy3` float NOT NULL DEFAULT '0',
  `toyposy4` float NOT NULL DEFAULT '0',
  `toyposz0` float NOT NULL DEFAULT '0',
  `toyposz1` float NOT NULL DEFAULT '0',
  `toyposz2` float NOT NULL DEFAULT '0',
  `toyposz3` float NOT NULL DEFAULT '0',
  `toyposz4` float NOT NULL DEFAULT '0',
  `toyrotx0` float NOT NULL DEFAULT '0',
  `toyrotx1` float NOT NULL DEFAULT '0',
  `toyrotx2` float NOT NULL DEFAULT '0',
  `toyrotx3` float NOT NULL DEFAULT '0',
  `toyrotx4` float NOT NULL DEFAULT '0',
  `toyroty0` float NOT NULL DEFAULT '0',
  `toyroty1` float NOT NULL DEFAULT '0',
  `toyroty2` float NOT NULL DEFAULT '0',
  `toyroty3` float NOT NULL DEFAULT '0',
  `toyroty4` float NOT NULL DEFAULT '0',
  `toyrotz0` float NOT NULL DEFAULT '0',
  `toyrotz1` float NOT NULL DEFAULT '0',
  `toyrotz2` float NOT NULL DEFAULT '0',
  `toyrotz3` float NOT NULL DEFAULT '0',
  `toyrotz4` float NOT NULL DEFAULT '0',
  `mod0` int NOT NULL DEFAULT '0',
  `mod1` int NOT NULL DEFAULT '0',
  `mod2` int NOT NULL DEFAULT '0',
  `mod3` int NOT NULL DEFAULT '0',
  `mod4` int NOT NULL DEFAULT '0',
  `mod5` int NOT NULL DEFAULT '0',
  `mod6` int NOT NULL DEFAULT '0',
  `mod7` int NOT NULL DEFAULT '0',
  `mod8` int NOT NULL DEFAULT '0',
  `mod9` int NOT NULL DEFAULT '0',
  `mod10` int NOT NULL DEFAULT '0',
  `mod11` int NOT NULL DEFAULT '0',
  `mod12` int NOT NULL DEFAULT '0',
  `mod13` int NOT NULL DEFAULT '0',
  `mod14` int NOT NULL DEFAULT '0',
  `mod15` int NOT NULL DEFAULT '0',
  `mod16` int NOT NULL DEFAULT '0',
  `vehPaintjob` int NOT NULL DEFAULT '-1',
  `vehState` int NOT NULL DEFAULT '0',
  `vehType` int NOT NULL DEFAULT '0',
  `vehFactionType` int NOT NULL DEFAULT '0',
  `vehPrice` int NOT NULL DEFAULT '0',
  `vehGarage` int NOT NULL DEFAULT '-1',
  `vehImpound` int NOT NULL DEFAULT '0',
  `vehImpoundPrice` int NOT NULL DEFAULT '0',
  `vehWeapon1` int NOT NULL DEFAULT '0',
  `vehWeapon2` int NOT NULL DEFAULT '0',
  `vehWeapon3` int NOT NULL DEFAULT '0',
  `vehAmmo1` int NOT NULL DEFAULT '0',
  `vehAmmo2` int NOT NULL DEFAULT '0',
  `vehAmmo3` int NOT NULL DEFAULT '0',
  `vehDurability1` int NOT NULL DEFAULT '0',
  `vehDurability2` int NOT NULL DEFAULT '0',
  `vehDurability3` int NOT NULL DEFAULT '0',
  `vehHighVelocity1` int NOT NULL DEFAULT '0',
  `vehHighVelocity2` int NOT NULL DEFAULT '0',
  `vehHighVelocity3` int NOT NULL DEFAULT '0',
  `vehTireLock` int NOT NULL DEFAULT '0',
  `vehEngineUpgrade` int NOT NULL DEFAULT '0',
  `vehBodyUpgrade` int NOT NULL DEFAULT '0',
  `vehNeon` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vehicle`
--

INSERT INTO `vehicle` (`vehID`, `vehModel`, `vehExtraID`, `vehX`, `vehY`, `vehZ`, `vehA`, `vehColor1`, `vehColor2`, `vehWorld`, `vehInterior`, `vehFuel`, `vehDamage1`, `vehDamage2`, `vehDamage3`, `vehDamage4`, `vehHealth`, `vehInsurance`, `vehInsuTime`, `vehLocked`, `vehPlate`, `vehRental`, `vehRentalTime`, `vehInsuranced`, `vehHouse`, `vehPark`, `vehWood`, `toyid0`, `toyid1`, `toyid2`, `toyid3`, `toyid4`, `toyposx0`, `toyposx1`, `toyposx2`, `toyposx3`, `toyposx4`, `toyposy0`, `toyposy1`, `toyposy2`, `toyposy3`, `toyposy4`, `toyposz0`, `toyposz1`, `toyposz2`, `toyposz3`, `toyposz4`, `toyrotx0`, `toyrotx1`, `toyrotx2`, `toyrotx3`, `toyrotx4`, `toyroty0`, `toyroty1`, `toyroty2`, `toyroty3`, `toyroty4`, `toyrotz0`, `toyrotz1`, `toyrotz2`, `toyrotz3`, `toyrotz4`, `mod0`, `mod1`, `mod2`, `mod3`, `mod4`, `mod5`, `mod6`, `mod7`, `mod8`, `mod9`, `mod10`, `mod11`, `mod12`, `mod13`, `mod14`, `mod15`, `mod16`, `vehPaintjob`, `vehState`, `vehType`, `vehFactionType`, `vehPrice`, `vehGarage`, `vehImpound`, `vehImpoundPrice`, `vehWeapon1`, `vehWeapon2`, `vehWeapon3`, `vehAmmo1`, `vehAmmo2`, `vehAmmo3`, `vehDurability1`, `vehDurability2`, `vehDurability3`, `vehHighVelocity1`, `vehHighVelocity2`, `vehHighVelocity3`, `vehTireLock`, `vehEngineUpgrade`, `vehBodyUpgrade`, `vehNeon`) VALUES
(1, 562, 1, -1753.28, -116.584, 3.60416, 327.26, 1, 1, 0, 0, 61, 0, 0, 0, 0, 1810, 3, 0, 0, 'NONE', -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1146, 1010, 1171, 1149, 0, 0, 0, 0, 1038, 1039, 1040, 0, 0, 0, 0, 1080, 0, 1, 0, 1, 0, 5000, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 18648),
(2, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(3, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(4, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(5, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(6, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(7, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(9, 560, 2, -2440.23, -642.835, 132.792, 195.576, -1, -1, 0, 0, 92, 0, 0, 0, 0, 1000, 3, 0, 1, 'NONE', -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 5000, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(10, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(11, 521, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(12, 560, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(13, 521, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(14, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(15, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(16, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(17, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(18, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(19, 522, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 'NONE', -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `vehiclekeys`
--

CREATE TABLE `vehiclekeys` (
  `ID` int NOT NULL,
  `playerID` int NOT NULL DEFAULT '-1',
  `vehicleID` int NOT NULL DEFAULT '-1',
  `vehicleModel` int NOT NULL DEFAULT '0',
  `vehicleKeyExists` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `vehicle_components`
--

CREATE TABLE `vehicle_components` (
  `componentid` smallint UNSIGNED NOT NULL,
  `part` enum('Exhausts','Front Bullbars','Front Bumper','Hood','Hydraulics','Lights','Misc','Rear Bullbars','Rear Bumper','Roof','Side Skirts','Spoilers','Vents','Wheels') DEFAULT NULL,
  `type` varchar(22) NOT NULL,
  `cars` smallint NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vehicle_components`
--

INSERT INTO `vehicle_components` (`componentid`, `part`, `type`, `cars`) VALUES
(1000, 'Spoilers', 'Pro', 0),
(1001, 'Spoilers', 'Win', 0),
(1002, 'Spoilers', 'Drag', 0),
(1003, 'Spoilers', 'Alpha', 0),
(1004, 'Hood', 'Champ Scoop', 0),
(1005, 'Hood', 'Fury Scoop', 0),
(1006, 'Roof', 'Roof Scoop', 0),
(1007, 'Side Skirts', 'Sideskirt', 0),
(1011, 'Hood', 'Race Scoop', 0),
(1012, 'Hood', 'Worx Scoop', 0),
(1013, 'Lights', 'Round Fog', 0),
(1014, 'Spoilers', 'Champ', 0),
(1015, 'Spoilers', 'Race', 0),
(1016, 'Spoilers', 'Worx', 0),
(1018, 'Exhausts', 'Upswept', 0),
(1019, 'Exhausts', 'Twin', 0),
(1020, 'Exhausts', 'Large', 0),
(1021, 'Exhausts', 'Medium', 0),
(1022, 'Exhausts', 'Small', 0),
(1023, 'Spoilers', 'Fury', 0),
(1024, 'Lights', 'Square Fog', 0),
(1025, 'Wheels', 'Offroad', 0),
(1027, 'Side Skirts', 'Alien', 560),
(1028, 'Exhausts', 'Alien', 560),
(1029, 'Exhausts', 'X-Flow', 560),
(1030, 'Side Skirts', 'X-Flow', 560),
(1032, 'Roof', 'Alien Roof Vent', 560),
(1033, 'Roof', 'X-Flow Roof Vent', 560),
(1034, 'Exhausts', 'Alien', 562),
(1035, 'Roof', 'X-Flow Roof Vent', 562),
(1037, 'Exhausts', 'X-Flow', 562),
(1038, 'Roof', 'Alien Roof Vent', 562),
(1039, 'Side Skirts', 'X-Flow', 562),
(1040, 'Side Skirts', 'Alien', 562),
(1043, 'Exhausts', 'Slamin', 575),
(1044, 'Exhausts', 'Chrome', 575),
(1045, 'Exhausts', 'X-Flow', 565),
(1046, 'Exhausts', 'Alien', 565),
(1049, 'Spoilers', 'Alien', 565),
(1050, 'Spoilers', 'X-Flow', 565),
(1051, 'Side Skirts', 'Alien', 565),
(1052, 'Side Skirts', 'X-Flow', 565),
(1053, 'Roof', 'X-Flow', 565),
(1054, 'Roof', 'Alien', 565),
(1055, 'Roof', 'Alien', 561),
(1058, 'Spoilers', 'Alien', 561),
(1059, 'Exhausts', 'X-Flow', 561),
(1060, 'Spoilers', 'X-Flow', 561),
(1061, 'Roof', 'X-Flow', 561),
(1062, 'Side Skirts', 'Alien', 561),
(1063, 'Side Skirts', 'X-Flow', 561),
(1064, 'Exhausts', 'Alien', 561),
(1065, 'Exhausts', 'Alien', 559),
(1066, 'Exhausts', 'X-Flow', 559),
(1067, 'Roof', 'Alien', 559),
(1068, 'Roof', 'X-Flow', 559),
(1071, 'Side Skirts', 'Alien', 559),
(1072, 'Side Skirts', 'X-Flow', 559),
(1073, 'Wheels', 'Shadow', -1),
(1074, 'Wheels', 'Mega', -1),
(1075, 'Wheels', 'Rimshine', -1),
(1076, 'Wheels', 'Wires', -1),
(1077, 'Wheels', 'Classic', -1),
(1078, 'Wheels', 'Twist', -1),
(1079, 'Wheels', 'Cutter', -1),
(1080, 'Wheels', 'Switch', -1),
(1081, 'Wheels', 'Grove', -1),
(1082, 'Wheels', 'Import', -1),
(1083, 'Wheels', 'Dollar', -1),
(1084, 'Wheels', 'Trance', -1),
(1085, 'Wheels', 'Atomic', -1),
(1087, 'Hydraulics', 'Hydraulics', -1),
(1088, 'Roof', 'Alien', 558),
(1089, 'Exhausts', 'X-Flow', 558),
(1091, 'Roof', 'X-Flow', 558),
(1092, 'Exhausts', 'Alien', 558),
(1094, 'Side Skirts', 'Alien', 558),
(1096, 'Wheels', 'Ahab', -1),
(1097, 'Wheels', 'Virtual', -1),
(1098, 'Wheels', 'Access', -1),
(1099, 'Side Skirts', 'Chrome', 575),
(1100, 'Misc', 'Chrome Grill', 534),
(1101, 'Side Skirts', 'Chrome Flames', 534),
(1102, 'Side Skirts', 'Chrome Strip', 567),
(1103, 'Roof', 'Covertible', 536),
(1104, 'Exhausts', 'Chrome', 536),
(1105, 'Exhausts', 'Slamin', 536),
(1107, 'Side Skirts', 'Chrome Strip', 536),
(1109, 'Rear Bullbars', 'Chrome', 535),
(1110, 'Rear Bullbars', 'Slamin', 535),
(1113, 'Exhausts', 'Chrome', 535),
(1114, 'Exhausts', 'Slamin', 535),
(1115, 'Front Bullbars', 'Chrome', 535),
(1116, 'Front Bullbars', 'Slamin', 535),
(1117, 'Front Bumper', 'Chrome', 535),
(1120, 'Side Skirts', 'Chrome Trim', 535),
(1121, 'Side Skirts', 'Wheelcovers', 535),
(1123, 'Misc', 'Bullbar Chrome Bars', 534),
(1124, 'Side Skirts', 'Chrome Arches', 534),
(1125, 'Misc', 'Bullbar Chrome Lights', 534),
(1126, 'Exhausts', 'Chrome', 534),
(1127, 'Exhausts', 'Slamin', 534),
(1128, 'Roof', 'Vinyl Hardtop', 536),
(1129, 'Exhausts', 'Chrome', 567),
(1130, 'Roof', 'Hardtop', 567),
(1131, 'Roof', 'Softtop', 567),
(1132, 'Exhausts', 'Slamin', 567),
(1135, 'Exhausts', 'Slamin', 576),
(1136, 'Exhausts', 'Chrome', 576),
(1137, 'Side Skirts', 'Chrome Strip', 576),
(1138, 'Spoilers', 'Alien', 560),
(1139, 'Spoilers', 'X-Flow', 560),
(1140, 'Rear Bumper', 'X-Flow', 560),
(1141, 'Rear Bumper', 'Alien', 560),
(1143, 'Vents', 'Oval Vents', 0),
(1145, 'Vents', 'Square Vents', 0),
(1146, 'Spoilers', 'X-Flow', 562),
(1147, 'Spoilers', 'Alien', 562),
(1148, 'Rear Bumper', 'X-Flow', 562),
(1149, 'Rear Bumper', 'Alien', 562),
(1150, 'Rear Bumper', 'Alien', 565),
(1151, 'Rear Bumper', 'X-Flow', 565),
(1152, 'Front Bumper', 'X-Flow', 565),
(1153, 'Front Bumper', 'Alien', 565),
(1154, 'Rear Bumper', 'Alien', 561),
(1155, 'Front Bumper', 'Alien', 561),
(1156, 'Rear Bumper', 'X-Flow', 561),
(1157, 'Front Bumper', 'X-Flow', 561),
(1158, 'Spoilers', 'X-Flow', 559),
(1159, 'Rear Bumper', 'Alien', 559),
(1160, 'Front Bumper', 'Alien', 559),
(1161, 'Rear Bumper', 'X-Flow', 559),
(1162, 'Spoilers', 'Alien', 559),
(1163, 'Spoilers', 'X-Flow', 558),
(1164, 'Spoilers', 'Alien', 558),
(1165, 'Front Bumper', 'X-Flow', 558),
(1166, 'Front Bumper', 'Alien', 558),
(1167, 'Rear Bumper', 'X-Flow', 558),
(1168, 'Rear Bumper', 'Alien', 558),
(1169, 'Front Bumper', 'Alien', 560),
(1170, 'Front Bumper', 'X-Flow', 560),
(1171, 'Front Bumper', 'Alien', 562),
(1172, 'Front Bumper', 'X-Flow', 562),
(1173, 'Front Bumper', 'X-Flow', 559),
(1174, 'Front Bumper', 'Chrome', 575),
(1175, 'Rear Bumper', 'Slamin', 575),
(1176, 'Front Bumper', 'Chrome', 575),
(1177, 'Rear Bumper', 'Slamin', 575),
(1178, 'Rear Bumper', 'Slamin', 534),
(1179, 'Front Bumper', 'Chrome', 534),
(1180, 'Rear Bumper', 'Chrome', 534),
(1181, 'Front Bumper', 'Slamin', 536),
(1182, 'Front Bumper', 'Chrome', 536),
(1183, 'Rear Bumper', 'Slamin', 536),
(1184, 'Rear Bumper', 'Chrome', 536),
(1185, 'Front Bumper', 'Slamin', 534),
(1186, 'Rear Bumper', 'Slamin', 567),
(1187, 'Rear Bumper', 'Chrome', 567),
(1188, 'Front Bumper', 'Slamin', 567),
(1189, 'Front Bumper', 'Chrome', 567),
(1190, 'Front Bumper', 'Slamin', 576),
(1191, 'Front Bumper', 'Chrome', 576),
(1192, 'Rear Bumper', 'Chrome', 576),
(1193, 'Rear Bumper', 'Slamin', 576);

-- --------------------------------------------------------

--
-- Table structure for table `vehicle_model_parts`
--

CREATE TABLE `vehicle_model_parts` (
  `modelid` smallint UNSIGNED NOT NULL,
  `parts` bit(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vehicle_model_parts`
--

INSERT INTO `vehicle_model_parts` (`modelid`, `parts`) VALUES
(400, b'100001101'),
(401, b'111111111'),
(402, b'100000100'),
(403, b'100000100'),
(404, b'101101101'),
(405, b'101000101'),
(407, b'100000000'),
(408, b'100000100'),
(409, b'100000100'),
(410, b'101111101'),
(411, b'100000100'),
(412, b'100000100'),
(413, b'100000100'),
(414, b'100000101'),
(415, b'101100101'),
(416, b'100000101'),
(418, b'101010101'),
(419, b'100000101'),
(420, b'101000111'),
(421, b'101000101'),
(422, b'100101101'),
(423, b'100000101'),
(424, b'100000100'),
(426, b'101010111'),
(427, b'100000101'),
(428, b'100000101'),
(429, b'100000100'),
(431, b'100000100'),
(432, b'100000000'),
(433, b'100000100'),
(434, b'100000100'),
(436, b'101111101'),
(437, b'100000100'),
(438, b'100000101'),
(439, b'111101100'),
(440, b'100000101'),
(441, b'100000100'),
(442, b'100000100'),
(443, b'100000000'),
(445, b'100000101'),
(451, b'100000100'),
(455, b'100000100'),
(456, b'100000101'),
(457, b'100000100'),
(458, b'111101101'),
(459, b'100000100'),
(466, b'100000101'),
(467, b'100000101'),
(470, b'100000100'),
(474, b'100000101'),
(475, b'100000101'),
(477, b'100110101'),
(478, b'100001111'),
(479, b'100000101'),
(480, b'100000101'),
(482, b'100000101'),
(483, b'100000101'),
(485, b'100000100'),
(486, b'100000000'),
(489, b'101011111'),
(490, b'101010111'),
(491, b'111100101'),
(492, b'101010111'),
(494, b'100000100'),
(495, b'100000101'),
(496, b'111111111'),
(498, b'100000101'),
(499, b'100000101'),
(500, b'100001101'),
(502, b'100000100'),
(503, b'100000100'),
(504, b'100000101'),
(505, b'101011111'),
(506, b'100000101'),
(507, b'100000101'),
(508, b'100000101'),
(514, b'100000100'),
(515, b'100000100'),
(516, b'101100111'),
(517, b'111100101'),
(518, b'111111111'),
(524, b'100000000'),
(525, b'100000000'),
(526, b'100000101'),
(527, b'101110101'),
(528, b'100000100'),
(529, b'101110111'),
(530, b'100000000'),
(531, b'100000000'),
(532, b'100000100'),
(533, b'100000100'),
(540, b'111111111'),
(541, b'100000100'),
(542, b'111000101'),
(543, b'101110100'),
(544, b'100000100'),
(545, b'100000100'),
(546, b'111101111'),
(547, b'111000101'),
(549, b'111100111'),
(550, b'111011111'),
(551, b'101010111'),
(552, b'100000101'),
(554, b'100000101'),
(555, b'100000100'),
(566, b'100000101'),
(568, b'100000100'),
(571, b'100000100'),
(572, b'100000100'),
(574, b'100000100'),
(578, b'100000100'),
(579, b'101010101'),
(580, b'101110101'),
(582, b'100000101'),
(583, b'100000100'),
(585, b'111111101'),
(587, b'101000111'),
(588, b'100000100'),
(589, b'111111111'),
(594, b'100000100'),
(596, b'100000101'),
(597, b'100000101'),
(598, b'100000101'),
(599, b'101010111'),
(600, b'100111111'),
(601, b'100000000'),
(602, b'100000100'),
(603, b'111111101'),
(604, b'100000101'),
(605, b'101110101'),
(609, b'100000101');

-- --------------------------------------------------------

--
-- Table structure for table `vehicle_object`
--

CREATE TABLE `vehicle_object` (
  `id` int UNSIGNED NOT NULL,
  `model` int UNSIGNED DEFAULT NULL,
  `vehicle` int UNSIGNED DEFAULT NULL,
  `color` int DEFAULT NULL,
  `type` tinyint UNSIGNED DEFAULT NULL,
  `x` float DEFAULT NULL,
  `y` float DEFAULT NULL,
  `z` float DEFAULT NULL,
  `rx` float DEFAULT NULL,
  `ry` float DEFAULT NULL,
  `rz` float DEFAULT NULL,
  `text` varchar(32) DEFAULT 'Text',
  `font` varchar(24) DEFAULT NULL,
  `fontcolor` int UNSIGNED DEFAULT NULL,
  `fontsize` int UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `warnings`
--

CREATE TABLE `warnings` (
  `ID` int NOT NULL,
  `Owner` int NOT NULL DEFAULT '0',
  `Type` int NOT NULL DEFAULT '0',
  `Admin` varchar(24) NOT NULL DEFAULT 'Staff',
  `Reason` varchar(32) NOT NULL DEFAULT 'Unknown',
  `Date` varchar(40) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `weaponsettings`
--

CREATE TABLE `weaponsettings` (
  `Owner` int NOT NULL,
  `WeaponID` tinyint NOT NULL,
  `PosX` float DEFAULT '-0.116',
  `PosY` float DEFAULT '0.189',
  `PosZ` float DEFAULT '0.088',
  `RotX` float DEFAULT '0',
  `RotY` float DEFAULT '44.5',
  `RotZ` float DEFAULT '0',
  `Bone` tinyint NOT NULL DEFAULT '1',
  `Hidden` tinyint NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `weed`
--

CREATE TABLE `weed` (
  `ID` int NOT NULL,
  `PosX` float NOT NULL DEFAULT '0',
  `PosY` float NOT NULL DEFAULT '0',
  `PosZ` float NOT NULL DEFAULT '0',
  `Grow` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `weed`
--

INSERT INTO `weed` (`ID`, `PosX`, `PosY`, `PosZ`, `Grow`) VALUES
(1, -2090.54, 2698.12, 162.625, 20),
(2, -2088.9, 2693.46, 162.435, 20);

-- --------------------------------------------------------

--
-- Table structure for table `workshop`
--

CREATE TABLE `workshop` (
  `ID` int NOT NULL,
  `Owner` int NOT NULL DEFAULT '-1',
  `OwnerName` varchar(24) NOT NULL DEFAULT 'No Owner',
  `Name` varchar(24) NOT NULL DEFAULT 'None Workshop',
  `Vault` int NOT NULL DEFAULT '0',
  `Price` int NOT NULL DEFAULT '0',
  `Locked` int NOT NULL DEFAULT '0',
  `FootX` float NOT NULL DEFAULT '0',
  `FootY` float NOT NULL DEFAULT '0',
  `FootZ` float NOT NULL DEFAULT '0',
  `VehX` float NOT NULL DEFAULT '0',
  `VehY` float NOT NULL DEFAULT '0',
  `VehZ` float NOT NULL DEFAULT '0',
  `VehA` float NOT NULL DEFAULT '0',
  `World` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `workshop`
--

INSERT INTO `workshop` (`ID`, `Owner`, `OwnerName`, `Name`, `Vault`, `Price`, `Locked`, `FootX`, `FootY`, `FootZ`, `VehX`, `VehY`, `VehZ`, `VehA`, `World`) VALUES
(1, 1, 'Dije_Yusuf', '-', 0, 100, 0, -1651.29, 437.36, 7.1797, 0, 0, 0, 0, 101);

-- --------------------------------------------------------

--
-- Table structure for table `workshop_employee`
--

CREATE TABLE `workshop_employee` (
  `ID` int NOT NULL,
  `Name` varchar(24) NOT NULL,
  `WorkshopID` int NOT NULL DEFAULT '-1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `911calls`
--
ALTER TABLE `911calls`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `acc_preset`
--
ALTER TABLE `acc_preset`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `actors`
--
ALTER TABLE `actors`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `aksesoris`
--
ALTER TABLE `aksesoris`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `arrest`
--
ALTER TABLE `arrest`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `atm`
--
ALTER TABLE `atm`
  ADD PRIMARY KEY (`atmID`);

--
-- Indexes for table `banip`
--
ALTER TABLE `banip`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `banneds`
--
ALTER TABLE `banneds`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `business`
--
ALTER TABLE `business`
  ADD PRIMARY KEY (`bizID`);

--
-- Indexes for table `business_queue`
--
ALTER TABLE `business_queue`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `carstorage`
--
ALTER TABLE `carstorage`
  ADD PRIMARY KEY (`itemID`);

--
-- Indexes for table `changenamesweb`
--
ALTER TABLE `changenamesweb`
  ADD PRIMARY KEY (`cnID`);

--
-- Indexes for table `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`pID`);

--
-- Indexes for table `contacts`
--
ALTER TABLE `contacts`
  ADD PRIMARY KEY (`contactID`);

--
-- Indexes for table `crates`
--
ALTER TABLE `crates`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `crime_record`
--
ALTER TABLE `crime_record`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `damagelog`
--
ALTER TABLE `damagelog`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `dealer`
--
ALTER TABLE `dealer`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `dealervehicle`
--
ALTER TABLE `dealervehicle`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `donation_characters`
--
ALTER TABLE `donation_characters`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `donation_code`
--
ALTER TABLE `donation_code`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `doors`
--
ALTER TABLE `doors`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `dropped`
--
ALTER TABLE `dropped`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `factiongarage`
--
ALTER TABLE `factiongarage`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `factiongaragevehs`
--
ALTER TABLE `factiongaragevehs`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `factions`
--
ALTER TABLE `factions`
  ADD PRIMARY KEY (`factionID`);

--
-- Indexes for table `factionvehicle`
--
ALTER TABLE `factionvehicle`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `familys`
--
ALTER TABLE `familys`
  ADD PRIMARY KEY (`familyID`);

--
-- Indexes for table `familystorage`
--
ALTER TABLE `familystorage`
  ADD PRIMARY KEY (`itemID`);

--
-- Indexes for table `flat`
--
ALTER TABLE `flat`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `flatkeys`
--
ALTER TABLE `flatkeys`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `flatstorage`
--
ALTER TABLE `flatstorage`
  ADD PRIMARY KEY (`itemID`);

--
-- Indexes for table `flat_queue`
--
ALTER TABLE `flat_queue`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `fuelpump`
--
ALTER TABLE `fuelpump`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `furniture`
--
ALTER TABLE `furniture`
  ADD PRIMARY KEY (`furnitureID`);

--
-- Indexes for table `garage`
--
ALTER TABLE `garage`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `gaterequests`
--
ALTER TABLE `gaterequests`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `gates`
--
ALTER TABLE `gates`
  ADD PRIMARY KEY (`gateID`);

--
-- Indexes for table `housekeys`
--
ALTER TABLE `housekeys`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `houses`
--
ALTER TABLE `houses`
  ADD PRIMARY KEY (`houseID`);

--
-- Indexes for table `housestorage`
--
ALTER TABLE `housestorage`
  ADD PRIMARY KEY (`itemID`);

--
-- Indexes for table `house_queue`
--
ALTER TABLE `house_queue`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `inventory`
--
ALTER TABLE `inventory`
  ADD PRIMARY KEY (`invID`);

--
-- Indexes for table `object`
--
ALTER TABLE `object`
  ADD PRIMARY KEY (`mobjID`);

--
-- Indexes for table `parks`
--
ALTER TABLE `parks`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `playersalary`
--
ALTER TABLE `playersalary`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `playerucp`
--
ALTER TABLE `playerucp`
  ADD PRIMARY KEY (`pID`);

--
-- Indexes for table `race_cps`
--
ALTER TABLE `race_cps`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `race_list`
--
ALTER TABLE `race_list`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `rental`
--
ALTER TABLE `rental`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `rock`
--
ALTER TABLE `rock`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `samacc`
--
ALTER TABLE `samacc`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `speedcameras`
--
ALTER TABLE `speedcameras`
  ADD PRIMARY KEY (`speedID`);

--
-- Indexes for table `tags`
--
ALTER TABLE `tags`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `tickets`
--
ALTER TABLE `tickets`
  ADD PRIMARY KEY (`ticketID`);

--
-- Indexes for table `toys`
--
ALTER TABLE `toys`
  ADD PRIMARY KEY (`Id`),
  ADD UNIQUE KEY `id` (`Owner`);

--
-- Indexes for table `trash`
--
ALTER TABLE `trash`
  ADD PRIMARY KEY (`TrashID`);

--
-- Indexes for table `tree`
--
ALTER TABLE `tree`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `vehicle`
--
ALTER TABLE `vehicle`
  ADD PRIMARY KEY (`vehID`);

--
-- Indexes for table `vehiclekeys`
--
ALTER TABLE `vehiclekeys`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `vehicleID` (`vehicleID`),
  ADD KEY `ID` (`ID`);

--
-- Indexes for table `vehicle_components`
--
ALTER TABLE `vehicle_components`
  ADD PRIMARY KEY (`componentid`),
  ADD KEY `cars` (`cars`),
  ADD KEY `part` (`part`),
  ADD KEY `type` (`type`);

--
-- Indexes for table `vehicle_model_parts`
--
ALTER TABLE `vehicle_model_parts`
  ADD PRIMARY KEY (`modelid`);

--
-- Indexes for table `vehicle_object`
--
ALTER TABLE `vehicle_object`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `warnings`
--
ALTER TABLE `warnings`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `weaponsettings`
--
ALTER TABLE `weaponsettings`
  ADD PRIMARY KEY (`Owner`,`WeaponID`),
  ADD UNIQUE KEY `Owner` (`Owner`,`WeaponID`);

--
-- Indexes for table `weed`
--
ALTER TABLE `weed`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `workshop`
--
ALTER TABLE `workshop`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `workshop_employee`
--
ALTER TABLE `workshop_employee`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `911calls`
--
ALTER TABLE `911calls`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `acc_preset`
--
ALTER TABLE `acc_preset`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `actors`
--
ALTER TABLE `actors`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=150;

--
-- AUTO_INCREMENT for table `aksesoris`
--
ALTER TABLE `aksesoris`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `arrest`
--
ALTER TABLE `arrest`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `atm`
--
ALTER TABLE `atm`
  MODIFY `atmID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=250;

--
-- AUTO_INCREMENT for table `banip`
--
ALTER TABLE `banip`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `banneds`
--
ALTER TABLE `banneds`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `business`
--
ALTER TABLE `business`
  MODIFY `bizID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `business_queue`
--
ALTER TABLE `business_queue`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `carstorage`
--
ALTER TABLE `carstorage`
  MODIFY `itemID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `changenamesweb`
--
ALTER TABLE `changenamesweb`
  MODIFY `cnID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `pID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `contacts`
--
ALTER TABLE `contacts`
  MODIFY `contactID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `crates`
--
ALTER TABLE `crates`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `crime_record`
--
ALTER TABLE `crime_record`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `damagelog`
--
ALTER TABLE `damagelog`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `dealer`
--
ALTER TABLE `dealer`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `dealervehicle`
--
ALTER TABLE `dealervehicle`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `donation_characters`
--
ALTER TABLE `donation_characters`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `donation_code`
--
ALTER TABLE `donation_code`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `dropped`
--
ALTER TABLE `dropped`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `factiongarage`
--
ALTER TABLE `factiongarage`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `factiongaragevehs`
--
ALTER TABLE `factiongaragevehs`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `factionID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT for table `factionvehicle`
--
ALTER TABLE `factionvehicle`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `familys`
--
ALTER TABLE `familys`
  MODIFY `familyID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `familystorage`
--
ALTER TABLE `familystorage`
  MODIFY `itemID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `flat`
--
ALTER TABLE `flat`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `flatkeys`
--
ALTER TABLE `flatkeys`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `flatstorage`
--
ALTER TABLE `flatstorage`
  MODIFY `itemID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `flat_queue`
--
ALTER TABLE `flat_queue`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `fuelpump`
--
ALTER TABLE `fuelpump`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `furniture`
--
ALTER TABLE `furniture`
  MODIFY `furnitureID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `garage`
--
ALTER TABLE `garage`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `gaterequests`
--
ALTER TABLE `gaterequests`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `gates`
--
ALTER TABLE `gates`
  MODIFY `gateID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `housekeys`
--
ALTER TABLE `housekeys`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `houses`
--
ALTER TABLE `houses`
  MODIFY `houseID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `housestorage`
--
ALTER TABLE `housestorage`
  MODIFY `itemID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `house_queue`
--
ALTER TABLE `house_queue`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `inventory`
--
ALTER TABLE `inventory`
  MODIFY `invID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `object`
--
ALTER TABLE `object`
  MODIFY `mobjID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=80;

--
-- AUTO_INCREMENT for table `parks`
--
ALTER TABLE `parks`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `playersalary`
--
ALTER TABLE `playersalary`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `playerucp`
--
ALTER TABLE `playerucp`
  MODIFY `pID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `race_cps`
--
ALTER TABLE `race_cps`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `race_list`
--
ALTER TABLE `race_list`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `rental`
--
ALTER TABLE `rental`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `rock`
--
ALTER TABLE `rock`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=123;

--
-- AUTO_INCREMENT for table `samacc`
--
ALTER TABLE `samacc`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `speedcameras`
--
ALTER TABLE `speedcameras`
  MODIFY `speedID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `tags`
--
ALTER TABLE `tags`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `tickets`
--
ALTER TABLE `tickets`
  MODIFY `ticketID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `toys`
--
ALTER TABLE `toys`
  MODIFY `Id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `trash`
--
ALTER TABLE `trash`
  MODIFY `TrashID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=51;

--
-- AUTO_INCREMENT for table `tree`
--
ALTER TABLE `tree`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=129;

--
-- AUTO_INCREMENT for table `vehicle`
--
ALTER TABLE `vehicle`
  MODIFY `vehID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT for table `vehiclekeys`
--
ALTER TABLE `vehiclekeys`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `vehicle_object`
--
ALTER TABLE `vehicle_object`
  MODIFY `id` int UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `warnings`
--
ALTER TABLE `warnings`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `weed`
--
ALTER TABLE `weed`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `workshop`
--
ALTER TABLE `workshop`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `workshop_employee`
--
ALTER TABLE `workshop_employee`
  MODIFY `ID` int NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
