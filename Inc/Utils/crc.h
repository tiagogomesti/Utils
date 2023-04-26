/**
 * @file crc.h
 * @brief Macros e protótipos de funções para cálculo de CRC
 *
 * @ingroup crc
 * @version 0.1
 * @date 2017-08-21
 * @author Fernando Almeida
 */

/**
 * @defgroup crc Crc
 * @ingroup misc
 * @{
 */

#ifndef __CRC_H__
#define __CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------
 *                 Includes
 *---------------------------------------------*/

/* Libc */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*----------------------------------------------
 *              Tipos de dados
 *---------------------------------------------*/

/** Tipo de CRC utilizado */
typedef enum crc_algorithm
{
    /** CRC de 16 bits */
    CRC16,
} crc_algorithm_t;

/** Tipo de dados de um CRC */
typedef struct crc
{
    /** Algoritmo utilizado no calculo de um CRC */
    crc_algorithm_t algorithm;
    union
    {
        /** Dados de um CRC de 16 bits */
        uint16_t crc16;
    };
} crc_t;

/*----------------------------------------------
 *            Protótipos e funções
 *---------------------------------------------*/

/* Inicia um objeto para calculo de um CRC */
bool crc_init(crc_t *crc, crc_algorithm_t algorithm);

/* Atualiza o valor do CRC com os dados apontos por buffer */
bool crc_update(crc_t *crc, uint8_t *buffer, size_t buffer_len);

/* Atualiza o valor do CRC com o valor de byte */
bool crc_update_by_byte(crc_t *crc, uint8_t byte);

/**
 * @brief Obtém o valor do crc calculado até o momento.
 * @param crc Valor do objeto utilizado para o calculo do crc16.
 * @return O Valor do crc.
 */
static inline uint32_t crc_get_value(crc_t *crc)
{
    return crc->crc16;
}

#ifdef __cplusplus
}
#endif

#endif

/** @} */
